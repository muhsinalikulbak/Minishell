/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:44:02 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/06 18:25:08 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	start_heredoc(char *delimiter, int *fd, bool is_it_expandable)
{
	int			pipefd[2];
	pid_t		child_pid;
	t_segment	*segments;

	segments = get_segments(NULL);
	if (pipe(pipefd) == -1)
		return (false);
	heredoc_parent_signal_setup();
	child_pid = fork();
	if (child_pid == -1)
		return (close_pipefd(pipefd));
	if (child_pid == 0)
	{
		free_segment(segments, segments->segment_count);
		heredoc_child_process(delimiter, pipefd, is_it_expandable);
		exit(EXIT_SUCCESS);
	}
	return (heredoc_parent_process(pipefd, child_pid, fd));
}

static bool	heredoc_scan(t_redir *redir)
{
	bool	is_it_expandable;
	char	*delimiter;
	int		i;

	i = 0;
	while (i < redir->redir_count)
	{
		if (redir[i].type == HEREDOC)
		{
			delimiter = redir[i].file_name;
			is_it_expandable = redir[i].state == STATE_NORMAL;
			if (!start_heredoc(delimiter, &redir[i].heredoc_fd, is_it_expandable))
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
