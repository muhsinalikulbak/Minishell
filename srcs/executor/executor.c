/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:29:56 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/05 17:07:07 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	single_command_builtin(t_segment *segment)
{
	int		saved_stdout;
	int 	saved_stdin;
	bool	redirect_ok;

	redirect_ok = true;
	if (segment->redirections)
	{
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		redirect_ok = handle_redirections(segment->redirections, false);
	}
	if (redirect_ok)
		execute_builtin(segment, false);
	if (segment->redirections)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
	}
}

static void	start_external(t_segment *segments, int seg_count, pid_t *pids)
{
	int		(*pipefd)[2];

	pipefd = NULL;
	if (seg_count - 1 > 0)
	{
		pipefd = malloc(sizeof(int [2]) * (seg_count - 1));
		if (!pipefd)
		{
			ft_putendl_fd("memory allocation failed", 2);
			return ;
		}
		if (!open_pipefd(pipefd, seg_count - 1))
		{
			ft_putendl_fd("pipe() function failed", 2);
			free(pipefd);
			return ;
		}
	}
	segments->pipefd = pipefd;
	process_setup(segments, pids, pipefd);
	free(pipefd);
}

void	executor(t_segment *segments)
{
	int		seg_count;
	pid_t	*pids;

	seg_count = segments->segment_count;
	if (seg_count == 1 && segments->cmd_type == CMD_BUILTIN)
		single_command_builtin(segments);
	else
	{
		pids = malloc(sizeof(pid_t) * seg_count);
		if (!pids)
		{
			ft_putendl_fd("memory allocation failed", 2);
			return ;
		}
		segments->pids = pids;
		start_external(segments, seg_count, pids);
		free(pids);
	}
	segments->pids = NULL;
	segments->pipefd = NULL;
}
