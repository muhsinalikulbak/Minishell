/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:52:32 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/08/07 01:19:47 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*print_err_segment(t_token *token, char *message)
{
	ft_putendl_fd(message, 2);
	free_token(token);
	return (NULL);
}

static bool	segment(t_token *token, t_segment *segments, int seg_count)
{
	if (!create_segment(token, segments, seg_count))
		return (print_err_segment(token, "memory allocation failed"));
	free_token(token);
	set_exit_code(0);
	if (!heredoc_init(segments))
	{
		if (get_exit_code() != 130)
			ft_putendl_fd("heredoc initialization failed", 2);
		return (NULL);
	}
	return (segments);
}

t_segment	*parser(t_token *token)
{
	t_segment	*segments;
	int			seg_count;

	seg_count = get_segment_count(token);
	segments = malloc(sizeof(t_segment) * seg_count);
	if (!segments)
		return (print_err_segment(token, "Memory allocation failed"));
	segments->pids = NULL;
	segments->pipefd = NULL;
	if (!segment(token, segments, seg_count))
	{
		free_segment(segments, seg_count);
		return (NULL);
	}
	if (!find_cmd(segments))
	{
		free_segment(segments, seg_count);
		return (NULL);
	}
	return (segments);
}
