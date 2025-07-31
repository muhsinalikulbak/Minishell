/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:57:07 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/31 22:31:10 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_last_token(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next != NULL)
		token = token->next;
	return (token);
}

int	get_token_count(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL)
	{
		count++;
		token = token->next;
	}
	return (count);
}

void	free_token(t_token *token)
{
	t_token	*next;

	if (get_token_count(token) == 0 || !token)
		return ;
	while (token != NULL)
	{
		next = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = next;
	}
}

static bool	token_add_back(t_lexer_data *data, t_token_type token_type)
{
	t_token	*new_token;
	t_token	*last;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		ft_putendl_fd("memory allocation failed", 2);
		return (free(data->token_value), false);
	}
	new_token->state = data->prev_state;
	new_token->value = data->token_value;
	new_token->type = token_type;
	new_token->is_ambiguous = data->is_ambiguous;
	new_token->empty_string = data->empty_string;
	new_token->next = NULL;
	new_token->prev = NULL;
	last = get_last_token(*data->token);
	if (last == NULL)
		*data->token = new_token;
	else
	{
		last->next = new_token;
		new_token->prev = last;
	}
	return (true);
}

bool	tokenizer(t_lexer_data *data)
{
	t_token_type	token_type;
	t_token_state	prev_state;

	prev_state = data->prev_state;
	if (prev_state == STATE_IN_DQUOTE || prev_state == STATE_IN_SQUOTE)
	{
		return (token_add_back(data, WORD));
	}
	else if (str_equal(data->token_value, "|"))
		token_type = PIPE;
	else if (str_equal(data->token_value, "<"))
		token_type = REDIR_IN;
	else if (str_equal(data->token_value, ">"))
		token_type = REDIR_OUT;
	else if (str_equal(data->token_value, "<<"))
		token_type = HEREDOC;
	else if (str_equal(data->token_value, ">>"))
		token_type = APPEND;
	else
		token_type = WORD;
	return (token_add_back(data, token_type));
}
/*
// Bu en son silinecek
void print_token_list(t_token *list)
{
    t_token *ptr;
    if (!list)
    {
        printf("\033[1;31m[Error] Empty token list\033[0m\n");
        return;
    }

    char *token_type[] = {
        "WORD", 
        "PIPE", 
        "REDIR_IN", 
        "REDIR_OUT", 
        "APPEND", 
        "HEREDOC", 
        NULL
    };

    int max_len = 0;
    ptr = list;
    while (ptr)
    {
        int len = ft_strlen(ptr->value);
        if (len > max_len)
            max_len = len;
        ptr = ptr->next;
    }

    ptr = list;
    printf("\033[1;32m--- TOKEN LIST ---\033[0m\n");

    while (ptr)
    {
        printf("\033[1;34m[Token]\033[0m ");
        printf("\"%s\"", ptr->value);
        int token_len = (int)strlen(ptr->value) + 2;
        for (int i = 0; i < max_len + 2 - token_len; i++)
            putchar(' ');
        printf(" \033[1;36mType\033
		[0m: \033[1;33m%s\
			033[0m\n", token_type[ptr->type]);
        ptr = ptr->next;
    }

    printf("\033[1;32m--- End of Token List ---\033[0m\n");
}*/
