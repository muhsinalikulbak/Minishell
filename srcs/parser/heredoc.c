/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:13:32 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/15 00:08:12 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	no_expand_heredoc(t_redir *redir)
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
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
		line = get_input(true);
		if (!line)
			return (close_pipefd(pipefd));
	}
	free(line);
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (true);
}

static bool	expand_heredoc(t_redir *redir) // Expand'de $'lı line gelirse expand edilicek ama delimiter ile karşılaştırılmayacak
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
		/* code */
	}
	return (true);
}

static bool	set_heredoc(t_redir *redir)
{
	int	i;

	i = 0;
	while (i < redir->redir_count)
	{
		if (redir[i].type == TOKEN_HEREDOC)
		{
			if (redir[i].state >= 1 && redir[i].state <= 2)
			{
				if (!no_expand_heredoc(&redir[i]))
					return (false);
			}
			else if (!expand_heredoc(&redir[i]))
				return (false);
		}
		i++;
	}
	return (true);
}

bool    heredoc(t_segment *segments)
{
	int		i;
	t_redir	*redir;

	i = 0;
	while (i < segments->segment_count)
	{
		redir = segments[i].redirections;
		if (redir)
		{
			if (!set_heredoc(redir))
				return (false);
		}
		i++;
	}
	return (true);
}
