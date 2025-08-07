/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:44:02 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/07 18:34:14 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	start_heredoc(char *delimiter, int *fd, bool is_it_expandable)
{
	int			pipefd[2];
	pid_t		child_pid;

	if (pipe(pipefd) == -1)
		return (false);
	heredoc_parent_signal_setup();
	child_pid = fork();
	if (child_pid == -1)
		return (close_pipefd(pipefd));
	if (child_pid == 0)
	{
		heredoc_child_process(delimiter, pipefd, is_it_expandable);
		exit(EXIT_SUCCESS);
	}
	return (heredoc_parent_process(pipefd, child_pid, fd));
}

static bool	heredoc_scan(t_redir *redir)
{
	bool	is_it_expandable;
	char	*delim;
	int		i;

	i = 0;
	while (i < redir->redir_count)
	{
		if (redir[i].type == HEREDOC)
		{
			delim = redir[i].file_name;
			is_it_expandable = redir[i].state == STATE_NORMAL;
			if (!start_heredoc(delim, &redir[i].heredoc_fd, is_it_expandable))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	heredoc_init(t_segment *segments)
{
	int		i;
	t_redir	*redir;

	i = 0;
	while (i < segments->segment_count)
	{
		redir = segments[i].redirections;
		if (redir)
		{
			if (!heredoc_scan(redir))
				return (false);
		}
		i++;
	}
	return (true);
}
