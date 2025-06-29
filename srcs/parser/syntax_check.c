/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:08:38 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/30 00:46:24 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	redirection_check(t_token *token_list)
{
	t_token	*temp;
	t_token	*last;

	temp = token_list;
	last = get_last_token(token_list);
	if (last->type == TOKEN_REDIR_IN || last->type == TOKEN_REDIR_OUT
		|| last->type == TOKEN_HEREDOC || last->type == TOKEN_APPEND)
		return (false);
	while (temp != NULL && temp->next != NULL)
	{
		if (temp->type == TOKEN_REDIR_IN
			&& temp->next->type != TOKEN_WORD)
			return (false);
		else if (temp->type == TOKEN_REDIR_OUT
			&& temp->next->type != TOKEN_WORD)
			return (false);
		else if (temp->type == TOKEN_HEREDOC
			&& temp->next->type != TOKEN_WORD)
			return (false);
		else if (temp->type == TOKEN_APPEND
			&& temp->next->type != TOKEN_WORD)
			return (false);
		temp = temp->next;
	}
	return (true);
}

static bool	pipe_check(t_token *token_list)
{
	t_token	*temp;

	temp = token_list;
	if (temp->type == TOKEN_PIPE)
		return (false);
	if (get_last_token(token_list)->type == TOKEN_PIPE)
		return (false);
	while (temp != NULL)
	{
		if (temp->next != NULL)
		{
			if (temp->type == TOKEN_PIPE
				&& temp->next->type == TOKEN_PIPE)
				return (false);
		}
		temp = temp->next;
	}
	return (true);
}

bool	syntax_check(t_token *token_list)
{
	if (!pipe_check(token_list))
	{
		ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
		return (false);
	}
	if (!redirection_check(token_list))
	{
		ft_putendl_fd("bash: syntax error near unexpected token\n", 2);
	}
	return (true);
}
