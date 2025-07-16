/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:13:32 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/16 13:20:19 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	write_pipefd(char *line, int pipefd[])
{
	write(pipefd[1], line, ft_strlen(line));
	write(pipefd[1], "\n", 1);
	free(line);
}

static bool	heredoc_raw(t_redir *redir)
{
	int		pipefd[2];
	char	*delimiter;
	char	*line;

	if (pipe(pipefd) == -1)
		return (false);
	line = get_input(true);
	if (!line)
		return (close_pipefd(pipefd));
	delimiter = redir->filename;
	while (!str_equal(delimiter, line))
	{
		write_pipefd(line, pipefd);
		line = get_input(true);
		if (!line)
			return (close_pipefd(pipefd));
	}
	free(line);
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (true);
}

static char	*create_key(char *line)
{

}

static bool	heredoc_expand(t_redir *redir) // Expand'de $'lı line gelirse expand edilicek ama delimiter ile karşılaştırılmayacak
{
	int		pipefd[2];
	char	*delimiter;
	char	*line;

	if (pipe(pipefd) == -1)
		return (false);
	line = get_input(true);
	if (!line)
		return (close_pipefd(pipefd));
	delimiter = redir->filename;
	while (!str_equal(delimiter, line))
	{
		line = get_input(true);
		if (!line)
			return (close_pipefd(pipefd));
	}
	free(line);
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (true);
}

static bool	heredoc_scan(t_redir *redir)
{
	int	i;

	i = 0;
	while (i < redir->redir_count)
	{
		if (redir[i].type == TOKEN_HEREDOC)
		{
			if (redir[i].state >= 1 && redir[i].state <= 2)
			{
				if (!heredoc_expand(&redir[i]))
					return (false);
			}
			else if (!heredoc_raw(&redir[i]))
				return (false);
		}
		i++;
	}
	return (true);
}

bool    heredoc_init(t_segment *segments)
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
