/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:42:20 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/07 03:44:35 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_manager(int exit_code)
{
	t_map		*map;
	t_segment	*segments;

	map = *get_env_map(NULL);
	segments = get_segments(NULL);
	if (segments)
		free_segment(segments, segments->segment_count);
	if (map)
		free_map(map);
	exit(exit_code);
}
