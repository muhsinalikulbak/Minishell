/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:52:32 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/18 17:42:40 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_segment	*parser(t_token *token)
{
	t_segment	*segments;
	int			segment_count;

	if (!syntax_check(token))
		return (NULL);
	segment_count = get_segment_count(token);
	segments = malloc(sizeof(t_segment) * segment_count);
	if (!segments)
	{
		ft_putendl_fd("memory allocation failed", 2);
		return (NULL);
	}
	if (!create_segment(token, segments, segment_count))
	{
		ft_putendl_fd("memory allocation failed", 2);
		return (NULL);
	}
	if (!heredoc_init(segments))
	{
		ft_putendl_fd("heredoc initialization failed", 2);
		return (NULL);
	}
	return (segments);
}
