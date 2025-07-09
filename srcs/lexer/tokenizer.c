/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:57:07 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/09 02:48:32 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_last_token(t_token *token_head)
{	
	if (token_head == NULL)
		return (NULL);
	while (token_head->next != NULL)
		token_head = token_head->next;
	return (token_head);
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

void free_token(t_token **token_head)
{
	t_token *current;
	t_token *next;

	if (get_token_count(*token_head) == 0)
		return ;
	if (!token_head || !*token_head)
		return;
	current = *token_head;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

static bool	insert_token(t_token **token_head, t_token_type token_type, char *value)
{
	t_token *new_token;
	t_token	*last;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(value);
		return (false);
	}
	new_token->value = value;
	new_token->type = token_type;
	new_token->next = NULL;
	new_token->prev = NULL;
	last = get_last_token(*token_head);
	if (last == NULL)
		*token_head = new_token;
	else
	{
		last->next = new_token;
		new_token->prev = last;
	}
	return (true);
}

bool	tokenizer(t_lexer_data *data, t_token **token)
{
	t_token_type	token_type;
	t_token_state	prev_state;

	prev_state = data->prev_state;
	if (prev_state == STATE_IN_DQUOTE || prev_state == STATE_IN_SQUOTE)
	{
		return (insert_token(token, TOKEN_WORD, data->token_value));
	}
	else if (str_equal(data->token_value, "|"))
		token_type = TOKEN_PIPE;
	else if (str_equal(data->token_value, "<"))
		token_type = TOKEN_REDIR_IN;
	else if (str_equal(data->token_value, ">"))
		token_type = TOKEN_REDIR_OUT;
	else if (str_equal(data->token_value, "<<"))
		token_type = TOKEN_HEREDOC;
	else if (str_equal(data->token_value, ">>"))
		token_type = TOKEN_APPEND;
	else
		token_type = TOKEN_WORD;
	return (insert_token(token, token_type, data->token_value));
}



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
        "TOKEN_WORD", 
        "TOKEN_PIPE", 
        "TOKEN_REDIR_IN", 
        "TOKEN_REDIR_OUT", 
        "TOKEN_APPEND", 
        "TOKEN_HEREDOC", 
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
        printf(" \033[1;36mType\033[0m: \033[1;33m%s\033[0m\n", token_type[ptr->type]);
        ptr = ptr->next;
    }

    printf("\033[1;32m--- End of Token List ---\033[0m\n");
}

