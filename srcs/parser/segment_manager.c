/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:00:00 by mkulbak           #+#    #+#             */
/*   Updated: 2025/08/04 20:21:03 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_segment	*get_segments(t_segment *segments)
{
	static t_segment	*segment_list = NULL;

	if (segments)
		segment_list = segments;
	return (segment_list);
}
