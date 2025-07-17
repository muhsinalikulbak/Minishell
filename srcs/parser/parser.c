/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:52:32 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/17 17:21:20 by muhsin           ###   ########.fr       */
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
		return (NULL);
	if (!create_segment(token, segments, segment_count))
		return (NULL);
	if (!heredoc_init(segments))
		return (NULL);
	return (segments);
}
