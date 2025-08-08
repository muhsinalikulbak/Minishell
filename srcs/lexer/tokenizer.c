/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:57:07 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/08/08 11:31:49 by muhsin           ###   ########.fr       */
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
	last = get_last_token(*data->token);
	if (last == NULL)
		*data->token = new_token;
	else
		last->next = new_token;
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
