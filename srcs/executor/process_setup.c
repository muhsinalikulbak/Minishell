/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:21:48 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/27 14:39:41 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	kill_process(int *pids, int i)
{
    while (i >= 0)
    {
        kill(pids[i], SIGTERM);
        i--;
    }    
}

static void	wait_child_process(int *pids, int seg_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < seg_count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	set_exit_code(WEXITSTATUS(status));
}

bool	process_setup(t_segment *segments, int *pids, int pipefd[][2])
{
	int	i;

	i = 0;
	while (i < segments->segment_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			kill_process(pids, i - 1);
			return (false);
		}
		if (pids[i] == 0)
		{
			setup_pipes(pipefd, i, segments->segment_count - 1);
			// handle_redirections(segments[i].redirections);
			close_all_pipes(pipefd, segments->segment_count - 1);
			handle_command(&segments[i]);
		}
		i++;
	}
	close_all_pipes(pipefd, segments->segment_count - 1);
	wait_child_process(pids, segments->segment_count);
	return (true);
}
