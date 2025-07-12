/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:18:39 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/12 20:44:20 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_count_in_segment(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		if (token->type >= 2 && token->type <= 5)
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
