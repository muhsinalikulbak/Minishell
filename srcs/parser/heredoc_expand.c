/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:48:03 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/30 02:40:02 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_for_heredoc(char *line, int *i, bool *is_it_exit_code)
{
	char	*key;
	char	*value;
	int		j;

	j = ++(*i);
	if (ft_isdigit(line[j]))
		return ("");
	if (line[j] == '?')
	{
		value = ft_itoa(get_exit_code());
		if (!value)
			return (NULL);
		*is_it_exit_code = true;
		return (value);
	}
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

static bool	check_no_expand_for_heredoc(char *line, int i)
{
	char	ch;

	ch = line[i + 1];
	if (ch != '_' && ch != '?' && (!ft_isalnum(ch) || !ch))
		return (false);
	return (true);
}

bool	heredoc_expand(char *line, int pipefd[2])
{
	char	*value;
	int		i;
	bool	is_it_exit_code;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && check_no_expand_for_heredoc(line, i))
		{
			value = get_value_for_heredoc(line, &i, &is_it_exit_code);
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



