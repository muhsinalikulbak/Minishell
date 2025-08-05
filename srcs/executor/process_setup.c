/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:21:48 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/05 15:41:33 by muhsin           ###   ########.fr       */
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
	int	last_status = 0;

	i = 0;
	while (i < seg_count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
			{
				last_status = 130;
				if (i == 0)
                    write(STDERR_FILENO, "\n", 1);
			}
            else if (WTERMSIG(status) == SIGQUIT)
                last_status = 131;
			else
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	exec_restore_signals();
	set_exit_code(last_status);
}

static void	child_process(t_segment *segment, int pipefd[][2], int i)
{
	exec_child_signal_setup();	
	if (segment->segment_count - 1 != 0)
	{
		pipe_setup(pipefd, i, segment->segment_count);
		close_all_pipes(pipefd, segment->segment_count - 1);
	}
	if (segment->redirections)
		handle_redirections(segment->redirections, true);
	if (segment->args)
		handle_command(segment);
	exit(EXIT_SUCCESS);
}

void	process_setup(t_segment *segments, int *pids, int pipefd[][2])
{
	int	i;

	i = 0;
	while (i < segments->segment_count)
	{
		exec_parent_signal_setup();
		pids[i] = fork();
		if (pids[i] == -1)
		{
			kill_process(pids, i - 1);
			ft_putendl_fd("Fork error", 2);
			return ;
		}
		if (pids[i] == 0)
			child_process(&segments[i], pipefd, i);
		i++;
	}
	if (segments->segment_count - 1 != 0)
		close_all_pipes(pipefd, segments->segment_count - 1);
	wait_child_process(pids, segments->segment_count);
}
