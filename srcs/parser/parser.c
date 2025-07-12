/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:52:32 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/12 20:15:52 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_segment	*create_segment(t_token *token)
{
	t_segment	*segment;
	char		**args;
	int			redir_count;
	int			cmd_count;
	int			k;

	segment = malloc(sizeof(t_segment));
	if (!segment)
		return (NULL);
	k = 0;
	args = NULL;
	redir_count = redir_count_in_segment(token);
	cmd_count = token_count_in_segment(token) - (redir_count * 2);
	if (cmd_count > 0)
	{
		args = malloc(sizeof(char *) * (cmd_count + 1));
		if (!args)
			return (free(segment), NULL);
		while (token != NULL && token->type != TOKEN_PIPE)
		{
			if (token->type == TOKEN_WORD)
			{
				args[k] = ft_strdup(token->value);
				if (!args[k])
				{
					free(segment);
					return (free_all(args));
				}
				k++;
			}
			else if (token->type >= 2 && token->type <= 5)
				token = token->next;
				token = token->next;
		}
		args[k] = NULL;
	}
	segment->args = args;
	return (segment);
}

static t_token	*next_pipe(t_token *token)
{
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		token = token->next;
	}
	return (token);
}

t_redir	*create_redir(t_token *token)
{
	t_redir	*redir;
	int		redir_count;

	redir_count = redir_count_in_segment(token);
	redir = malloc(sizeof(t_redir) * redir_count);
	if (!redir)
		return (NULL);
	
}

t_segment	*parser(t_token *token)
{
	t_segment	*segments;
	t_segment	*segment;

	if (!syntax_check(token))
		return (NULL);
	segments = NULL;
	while (token != NULL)
	{
		segment = create_segment(token);
		if (!segment)
		{
			free_segments(segments);
			return (NULL);
		}
		segment->redirections = create_redir(token);
		segment_add_back(&segments, segment);
		// mevcuttaki segmenteki redirection'ları da al
		token = next_pipe(token);
	}
	return (NULL);
}
