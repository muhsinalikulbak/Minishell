/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:52:32 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/12 15:05:45 by muhsin           ###   ########.fr       */
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
			return (NULL);
		while (token != NULL && token->type != TOKEN_PIPE)
		{
			if (token->type == TOKEN_WORD)
			{
				args[k] = ft_strdup(token->value);
				if (!args[k])
					return (free_all(args));
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

static t_token *next_pipe(t_token *token)
{
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		token = token->next;
	}
	return (token);
}

static t_segment *get_last_segment(t_segment *segment)
{
	if (segment == NULL)
		return (NULL);
	while (segment->next != NULL)
	{
		segment = segment->next;
	}
	return (segment);
}

static void	segment_add_back(t_segment **segments, t_segment *segment)
{
	t_segment *last;

	if (*segments == NULL)
	{
		*segments = segment;
		return ;
	}
	last = get_last_segment(*segments);
	last->next = segment;
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
			// free_segments(segments);
			return (NULL);
		}
		segment_add_back(&segments, segment);
		// mevcuttaki segmenteki redirection'ları da al
		token = next_pipe(token);
	}


	return (NULL);
}
