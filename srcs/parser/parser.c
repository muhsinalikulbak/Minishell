/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:52:32 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/28 16:08:33 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_segment	*segment(t_token *token)
{
	int			segment_count;
	t_segment	*segments;

	segment_count = get_segment_count(token);
	segments = malloc(sizeof(t_segment) * segment_count);
	if (!segments)
	{
		ft_putendl_fd("memory allocation failed", 2);
		free_token(token);
		return (NULL);
	}
	if (!create_segment(token, segments, segment_count))
	{
		ft_putendl_fd("memory allocation failed", 2);
		free_token(token);
		return (NULL);
	}
	free_token(token);
	if (!heredoc_init(segments))
	{
		ft_putendl_fd("heredoc initialization failed", 2);
		return (NULL);
	}
	return (segments);
}

t_segment	*parser(t_token *token)
{
	t_segment	*segments;

	segments = segment(token);
	if (!segments)
		return (NULL);
	if (!find_cmd(segments))
	{
		free_segment(segments, segments->segment_count);
		return (NULL);
	}
	return (segments);
}
