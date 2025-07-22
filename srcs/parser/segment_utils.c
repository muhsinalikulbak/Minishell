/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:22:33 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/18 21:58:48 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_count_in_segment(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		if (token->type >= TOKEN_REDIR_IN && token->type <= TOKEN_HEREDOC)
			count++;
		token = token->next;
	}
	return (count);
}

int	token_count_in_segment(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		count++;
		token = token->next;
	}
	return (count);
}

int	get_segment_count(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL)
	{
		if (token->type == TOKEN_PIPE)
			count++;
		token = token->next;
	}
	return (count + 1);
}

t_token	*next_pipe(t_token *token)
{
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		token = token->next;
	}
	if (token != NULL)
		token = token->next;
	return (token);
}
