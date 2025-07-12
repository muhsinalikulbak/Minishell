/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:52:32 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/12 04:12:56 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_count_in_segment(t_token *token)
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

static int	token_count_in_segment(t_token *token)
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

static bool	create_segment(t_token *token, t_segment **segment)
{
	// Burada char **args oluştur
	//t_redirection oluştur ve ata
}

t_segment	**parser(t_token *token)
{
	t_segment	*segments;

	if (!syntax_check(token))
		return (NULL);
	segments = NULL;
	create_segment(token, &segments);
	// Burada tokenler pipe pipe ayrılacak
	// her pipe arası node olacak (t_cmd * olarak) 
	return (NULL);
}