/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:18:39 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/12 19:39:47 by mkulbak          ###   ########.fr       */
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

void	segment_add_back(t_segment **segments, t_segment *segment)
{
	t_segment	*last;

	if (*segments == NULL)
	{
		*segments = segment;
		return ;
	}
	last = get_last_segment(*segments);
	last->next = segment;
}

t_segment	*get_last_segment(t_segment *segment)
{
	if (segment == NULL)
		return (NULL);
	while (segment->next != NULL)
	{
		segment = segment->next;
	}
	return (segment);
}

void	free_segments(t_segment *segments)
{
	t_segment	*next_segment;
	t_redir		*next_redir;

	if (segments == NULL)
		return ;
	while (segments)
	{
		next_segment = segments->next;
		while (segments->redirections)
		{
			next_redir = segments->redirections->next;
			if (segments->redirections->filename)
				free(segments->redirections->filename);
			if (segments->redirections->heredoc_fd != -1)
				close(segments->redirections->heredoc_fd);
			free(segments->redirections);
			segments->redirections = next_redir;
		}
		if (segments->args)
			free_all(segments->args);
		free(segments);
		segments = next_segment;
	}
}
