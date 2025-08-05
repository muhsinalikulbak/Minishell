/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:42:20 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/05 13:44:10 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_manager()
{
	t_map		*map;
	t_segment	*segments;

	map = *get_env_map(NULL);
	segments = get_segments(NULL);
	free_segment(segments, segments->segment_count);
	free_map(map);
}
