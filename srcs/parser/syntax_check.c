/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 04:08:38 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/16 05:12:12 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	redirection_check(t_token *token_list)
{

	
}

static bool	pipe_check(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	if (current->type == TOKEN_PIPE)
		return (false);
	if (get_last_token(token_list)->type == TOKEN_PIPE)
		return (false);
	while (current != NULL)
	{
		if (current->next != NULL)
		{
			if (current->type == TOKEN_PIPE && current->next == TOKEN_PIPE)
				return (false);
		}
		current = current->next;
	}
	return (true);
}

bool	syntax_check(t_token *token_list)
{
	if (!pipe_check(token_list))
	{
		printf("bash: syntax error near unexpected token `|'");
	}
	return (true);
}
