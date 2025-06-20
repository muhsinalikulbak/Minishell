/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:52:24 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/20 11:25:52 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tokenize(char *cmd, t_token **token)
{
	int				len;
	t_token_type	token_type;
	
	len = ft_strlen(cmd);
	if (cmd[0] == '|' && len == 1)
		token_type = TOKEN_PIPE;
	else if (cmd[0] == '<' && len == 1)
		token_type = TOKEN_REDIR_IN;
	else if (cmd[0] == '>' && len == 1)
		token_type = TOKEN_REDIR_OUT;
	else if (cmd[0] == '<' && cmd[1] == '<' && len == 2)
		token_type = TOKEN_HEREDOC;
	else if (cmd[0] == '>' && cmd[1] == '>' && len == 2)
		token_type = TOKEN_APPEND;
	else
		token_type = TOKEN_WORD;
	insert_token(token, cmd, token_type);
}

static void split_line(char *input_cmd, t_token **token)
{
    int				i;
    int				j;
    char			*arg;
    t_token_state	state;
	t_token_state	prev_state;

	char **states = malloc(sizeof(char*) * 5);
	states[0] = "NORMAL";
	states[1] = "DQUOTE";
	states[2] = "SQUOTE";
	states[3] = "IDLE";
	states[4] = NULL;

    arg = NULL;
    i = 0;
    j = 0;
    state = STATE_IDLE;
    prev_state = STATE_NORMAL;
    while (input_cmd[i])
    {
        if (state == STATE_IDLE && input_cmd[i] != ' ')
        {
            state = STATE_NORMAL;
            if (arg == NULL)
            {
                arg = (char *)ft_calloc(ft_strlen(input_cmd) + 1, sizeof(char));
                j = 0;
            }
            if (input_cmd[i] == '"')
                state = STATE_IN_DQUOTE;
            else if (input_cmd[i] == '\'')
                state = STATE_IN_SQUOTE;
            else
                arg[j++] = input_cmd[i]; // Bu ilk ekleme olursa | < > gibi kontroller yapılmalı
        }
        else if (state == STATE_IN_DQUOTE)
        {
			prev_state = state;
            if (input_cmd[i] == '"')
                state = STATE_NORMAL;
            else
                arg[j++] = input_cmd[i];
        }
        else if (state == STATE_IN_SQUOTE)
        {
			prev_state = state;
            if (input_cmd[i] == '\'')
                state = STATE_NORMAL;
            else
                arg[j++] = input_cmd[i];
        }
        else if (state == STATE_NORMAL)
        {
            if (input_cmd[i] == ' ')
            {
                arg[j] = '\0';
                printf("extracked arg: %s  PREV_TOKEN : %s\n", arg, states[prev_state]);
                tokenize(arg, token);// Burada ne ile çıktığını yani prev state'i verip ona göre token node ekleyecek // NORMAL STATE NORMAL DEĞİLSE SYNTAX HATASI
                free(arg);
                arg = NULL;
				prev_state = state;
                state = STATE_IDLE;
            }
            else if (input_cmd[i] == '"')
			{
				prev_state = state;
                state = STATE_IN_DQUOTE;
			}
            else if (input_cmd[i] == '\'')
			{
				prev_state = state;
                state = STATE_IN_SQUOTE;
			}
            else
                arg[j++] = input_cmd[i]; // State Normal eklemede kontrol yapılıcak ls|cat pipe alınmalı ya da >> << < > alınmalı
        }
        i++;
    }
    if (arg != NULL)
    {
        arg[j] = '\0';
        printf("extracked arg: %s  PREV_TOKEN : %s\n", arg, states[prev_state]);
        tokenize(arg, token); // Burada ne ile çıktığını yani prev state'i verip ona göre token node ekleyecek // NORMAL STATE NORMAL DEĞİLSE SYNTAX HATASI
        free(arg);
    }
    return ;
}

t_token *lexer(char *command_line)
{
	t_token *token;
	token = NULL;
	split_line(command_line, &token);
    print_list(token);
	return token;
}
