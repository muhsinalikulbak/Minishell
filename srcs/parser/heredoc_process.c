/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:45:19 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/07 03:44:18 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_pipefd(char *line, int pipefd[2])
{
	write(pipefd[1], line, ft_strlen(line));
	write(pipefd[1], "\n", 1);
	free(line);
}

static void	process_heredoc_line(char *line, int pipefd[2],
				bool is_it_expandable)
{
	if (is_it_expandable && ft_strchr(line, '$'))
	{
		if (!heredoc_expand(line, pipefd))
		{
			close(pipefd[1]);
			cleanup_manager(EXIT_FAILURE);
		}
		write(pipefd[1], "\n", 1);
		free(line);
	}
	else
		write_pipefd(line, pipefd);
}

void	heredoc_child_process(char *delimiter, int pipefd[2],
		bool is_it_expandable)
{
	char		*line;

	heredoc_child_signal_setup();
	close(pipefd[0]);
	line = get_input(true);
	if (!line)
		handle_heredoc_eof(delimiter, pipefd);
	while (!str_equal(delimiter, line))
	{
		process_heredoc_line(line, pipefd, is_it_expandable);
		line = get_input(true);
		if (!line)
		{
			print_heredoc_warning(delimiter);
			close(pipefd[1]);
			cleanup_manager(EXIT_SUCCESS);
		}
	}
	free(line);
	close(pipefd[1]);
	cleanup_manager(EXIT_SUCCESS);
}

bool	heredoc_parent_process(int pipefd[2], pid_t child_pid, int *fd)
{
	int	status;

	close(pipefd[1]);
	waitpid(child_pid, &status, 0);
	heredoc_restore_signals();
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipefd[0]);
		*fd = -1;
		if (WEXITSTATUS(status) == 130)
			set_exit_code(130);
		else
			set_exit_code(WEXITSTATUS(status));
		return (false);
	}
	*fd = pipefd[0];
	return (true);
}


