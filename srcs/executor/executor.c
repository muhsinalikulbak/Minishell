/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:29:56 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/28 21:21:59 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	executor(t_segment *segments)
{
	int		(*pipefd)[2];
	pid_t	*pids;

	if (segments->segment_count == 1 && segments->cmd_type == CMD_BUILTIN)
	{
		execute_builtin(segments, false);
		return (true);
	}
	pids = malloc(sizeof(pid_t) * segments->segment_count);
	if (!pids)
	{
		ft_putendl_fd("memory allocation failed", 2);
		return (false);
	}
	if (segments->segment_count - 1 > 0)
	{
		pipefd = malloc(sizeof(int [2]) * (segments->segment_count - 1));
		if (!pipefd)
		{
			ft_putendl_fd("memory allocation failed", 2);
			return (free(pids), false);
		}
		if (!open_pipefd(pipefd, segments->segment_count - 1))
		{
			ft_putendl_fd("pipe() function failed", 2);
			free(pipefd);
			return (free(pids), false);
		}
	}
	process__setup(segments, pids, pipefd);
	free(pids);
	return (true);
}
