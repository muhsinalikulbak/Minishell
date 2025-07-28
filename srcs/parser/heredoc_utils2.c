/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:48:03 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/28 20:47:29 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_for_heredoc(char *line, int *i)
{
	char	*key;
	char	*value;
	int		j;

	j = ++(*i);
	if (ft_isdigit(line[j]))
		return ("");
	while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
		j++;
	key = ft_substr(line, *i, j - *i);
	if (!key)
		return (free(line), NULL);
	value = try_get_value(key);
	free(key);
	*i = j - 1;
	if (value == NULL)
		return ("");
	return (value);
}

bool	heredoc_expand(char *line, int pipefd[2])
{
	char	*value;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && check_no_expand_for_heredoc(line, i))
		{
			value = get_value_for_heredoc(line, &i);
			if (!value)
				return (free(line), false);
			write(pipefd[1], value, ft_strlen(value));
		}
		else
			write(pipefd[1], &line[i], 1);
		i++;
	}
	return (true);
}

void	handle_heredoc_eof(char *delimiter, int pipefd[2])
{
	ft_putstr_fd("bash: warning: here-document", 2);
	ft_putstr_fd("elimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
	close(pipefd[1]);
	exit(0);
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
