/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:52:24 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/18 23:30:06 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum s_token_state
{
	STATE_NORMAL,
	STATE_IN_DQUOTE,
	STATE_IN_SQUOTE,
    STATE_IDLE
}		t_token_state;

static bool is_special_char(char c) {
    return (c == '|' || c == '<' || c == '>');
}

static void	tokenize(char *cmd, t_token **token)
{
	int				len;
	t_token_type	token_type;
	
	len = ft_strlen(cmd);
	if (len == 1)
	{
		if (cmd[0] == '|')
		   token_type = TOKEN_PIPE;
		if (cmd[0] == '<')
		token_type = TOKEN_REDIR_IN;
		if (cmd[0] == '>')
		token_type = TOKEN_REDIR_OUT;
	}
	else if (len == 2)
	{
		if (cmd[0] == '<' && cmd[1] == '<')
		token_type = TOKEN_HEREDOC;
		if (cmd[0] == '>' && cmd[1] == '>')
		token_type = TOKEN_APPEND;
	}
	else
	token_type = TOKEN_WORD;
	insert_token(token, cmd, token_type);
}

static void split_line(char *input_cmd, t_token **token)
{
    int     i;
    int     j;
    char    *arg;
    t_token_state state;
    
    arg = NULL;
    i = 0;
    j = 0;
    state = STATE_IDLE;
    
    while (input_cmd[i])
    {
        if (state == STATE_IDLE && input_cmd[i] != ' ')
        {
            state = STATE_NORMAL;
            if (arg == NULL)
            {
                arg = (char *)ft_calloc((ft_strlen(input_cmd) + 1), sizeof(char));
                j = 0;
            }
            if (input_cmd[i] == '"')
                state = STATE_IN_DQUOTE;
            else if (input_cmd[i] == '\'')
                state = STATE_IN_SQUOTE;
            else
                arg[j++] = input_cmd[i];
        }
        else if (state == STATE_IN_DQUOTE)
        {
            if (input_cmd[i] == '"')
                state = STATE_NORMAL;
            else
                arg[j++] = input_cmd[i];
        }
        else if (state == STATE_IN_SQUOTE)
        {
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
                printf("extracked arg: %s\n", arg);
                tokenize(arg, token);
                free(arg);
                arg = NULL;
                state = STATE_IDLE;
            }
            else if (input_cmd[i] == '"')
                state = STATE_IN_DQUOTE;
            else if (input_cmd[i] == '\'')
                state = STATE_IN_SQUOTE;
            else
                arg[j++] = input_cmd[i];
        }
        i++;
    }
    if (arg != NULL)
    {
        arg[j] = '\0';
        printf("extracked arg:%s \n", arg);
        tokenize(arg, token);
        free(arg);
    }
    
    return;
}



t_token *lexer(char *command_line)
{
	t_token *token;
	token = NULL;
	split_line(command_line, &token);
    print_list(token);
	return token;   
}