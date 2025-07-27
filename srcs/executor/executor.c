/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:29:56 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/27 14:28:45 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirections(t_redir *redir)
{
	// int		i;

	// i = 0;
	// while (i < redir->redir_count)
	// {
	// 	if (redir[i].type == TOKEN_REDIR_IN || redir[i].type == TOKEN_HEREDOC)
	// 		dup2()
	// }
	
}

bool	executor(t_segment *segments)
{
	int	pipefd[segments->segment_count - 1][2];
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
	if (!open_pipefd(pipefd, segments->segment_count - 1))
	{
		ft_putendl_fd("pipe() function failed", 2);
		return (free (pids), false);
	}
	process_setup(segments, pids, pipefd);
	free(pids);
	return (true);
}
