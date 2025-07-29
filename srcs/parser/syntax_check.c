/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:08:38 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/29 03:07:25 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_redir_file(t_token *token, char **next_value)
{
	t_token	*last;

	last = get_last_token(token);
	if (last->type >= 2 && last->type <= 5)
		return (false);
	while (token != NULL && token->next != NULL)
	{
		*next_value = token->next->value;
		if (token->type == REDIR_IN
			&& token->next->type != WORD)
			return (false);
		else if (token->type == REDIR_OUT
			&& token->next->type != WORD)
			return (false);
		else if (token->type == HEREDOC
			&& token->next->type != WORD)
			return (false);
		else if (token->type == APPEND
			&& token->next->type != WORD)
			return (false);
		token = token->next;
	}
	return (true);
}

static bool	pipe_check(t_token *token)
{
	if (token->type == PIPE)
		return (false);
	if (get_last_token(token)->type == PIPE)
		return (false);
	while (token != NULL)
	{
		if (token->next != NULL)
		{
			if (token->type == PIPE
				&& token->next->type == PIPE)
				return (false);
		}
		token = token->next;
	}
	return (true);
}

bool	syntax_check(t_token *token_list)
{
	char	*next_value;

	if (!pipe_check(token_list))
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		set_exit_code(2);
		return (false);
	}
	if (!check_redir_file(token_list, &next_value))
	{
		ft_putstr_fd("syntax error near unexpected token ", 2);
		ft_putendl_fd(next_value, 2);
		set_exit_code(2);
		return (false);
	}
	return (true);
}
