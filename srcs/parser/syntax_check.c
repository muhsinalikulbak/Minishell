/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:08:38 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/18 17:58:56 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_redir_file(t_token *token, char **next_value)
{
	t_token	*last;

	last = get_last_token(token);
	if (last->type >= 2 && last->type <= 5)
		return (false); // Buradaki durumda unexpected token newline olacak. SADECE BU KISMI FONKSİYONA ALABİLİRİM
	while (token != NULL && token->next != NULL)
	{
		*next_value = token->next->value;
		if (token->type == TOKEN_REDIR_IN
			&& token->next->type != TOKEN_WORD)
			return (false);
		else if (token->type == TOKEN_REDIR_OUT
			&& token->next->type != TOKEN_WORD)
			return (false);
		else if (token->type == TOKEN_HEREDOC
			&& token->next->type != TOKEN_WORD)
			return (false);
		else if (token->type == TOKEN_APPEND
			&& token->next->type != TOKEN_WORD)
			return (false);
		token = token->next;
	}
	return (true);
}

static bool	pipe_check(t_token *token)
{
	if (token->type == TOKEN_PIPE)
		return (false);
	if (get_last_token(token)->type == TOKEN_PIPE)
		return (false);
	while (token != NULL)
	{
		if (token->next != NULL)
		{
			if (token->type == TOKEN_PIPE
				&& token->next->type == TOKEN_PIPE)
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
