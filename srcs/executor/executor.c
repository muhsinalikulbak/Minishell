/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:29:56 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/29 13:13:41 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_segment *segments)
{
	int		(*pipefd)[2];
	pid_t	*pids;

	pipefd = NULL;
	if (segments->segment_count == 1 && segments->cmd_type == CMD_BUILTIN)
	{
		if (segments->redirections)
			handle_redirections(segments->redirections);
		execute_builtin(segments, false);
	}
	else
	{
		pids = malloc(sizeof(pid_t) * segments->segment_count);
		if (!pids)
		{
			ft_putendl_fd("memory allocation failed", 2);
			return ;
		}
		if (segments->segment_count - 1 > 0)
		{
			pipefd = malloc(sizeof(int [2]) * (segments->segment_count - 1));
			if (!pipefd)
			{
				ft_putendl_fd("memory allocation failed", 2);
				free(pids);
				return ;
			}
			if (!open_pipefd(pipefd, segments->segment_count - 1))
			{
				ft_putendl_fd("pipe() function failed", 2);
				free(pipefd);
				free(pids);
				return ;
			}
		}
		process_setup(segments, pids, pipefd);
		if (pipefd)
			free(pipefd);
		free(pids);
	}
}
