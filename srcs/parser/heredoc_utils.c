/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:45:19 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/29 19:43:59 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_pipefd(char *line, int pipefd[2])
{
	write(pipefd[1], line, ft_strlen(line));
	write(pipefd[1], "\n", 1);
	free(line);
}

bool	heredoc_finishing(char *line, int pipefd[2], int *fd)
{
	(void) fd;
	free(line);
	close(pipefd[1]);
	return (true);
}

bool	check_no_expand_for_heredoc(char *line, int i)
{
	char	ch;

	ch = line[i + 1];
	if (ch != '_' && ch != '?' && (!ft_isalnum(ch) || !ch))
		return (false);
	return (true);
}
