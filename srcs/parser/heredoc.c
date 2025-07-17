/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:13:32 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/17 04:59:10 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool check_no_expand_for_heredoc(char *line, int i)
{
	if (line[i + 1] != '_' && (!ft_isalnum(line[i + 1]) || !line[i + 1]))
		return (true);
	return (false);
}

static char	*get_value_for_heredoc(char *line, char *expand_line, int i, t_map *map)
{
	int		j;
	char	*key;
	char	*value;

	(void)expand_line; // Şimdilik kullanılmıyor
	j = i;
	while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
		j++;
	key = ft_substr(line, i, j - i);
	if (!key)
		return (NULL);
	value = try_get_value(map, key);
	free(key);
	return (value);
}

static char	*heredoc_expand(char *line)
{
	char	*expand_line;
	int		i;

	expand_line = (char *)ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (!expand_line)
		return (free(line), NULL);
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			if (check_no_expand_for_heredoc(line, i))
				expand_line[i] = line[i];
			else
			{
				get_value_for_heredoc(line, expand_line, ++i, NULL); // ŞİMDİLİK T_MAP YERİNE NULL KOYULDU STATİC OLARAK ALINICAK
			}
		}
		else
			expand_line[i] = line[i];
	}
	return (expand_line);
}

static bool	heredoc(char *delimiter, int *fd, bool is_it_expandable)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (false);
	line = get_input(true);
	if (!line)
		return (close_pipefd(pipefd));
	while (!str_equal(delimiter, line))
	{
		if (!is_it_expandable || (is_it_expandable && !ft_strchr(line, '$')))
			write_pipefd(line, pipefd);
		else
		{
			line = heredoc_expand(line);
			write_pipefd(line, pipefd);
		}
		line = get_input(true);
		if (!line)
			return (close_pipefd(pipefd));
	}
	return (heredoc_finishing(line, pipefd, fd));
}

static bool	heredoc_scan(t_redir *redir)
{
	int		i;
	bool	is_it_expandable;

	i = 0;
	while (i < redir->redir_count)
	{
		if (redir[i].type == TOKEN_HEREDOC)
		{
			is_it_expandable = redir[i].state == STATE_NORMAL;
			if (!heredoc(redir[i].filename, &redir[i].heredoc_fd, is_it_expandable))
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
