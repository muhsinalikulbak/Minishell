/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:45:19 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/26 18:11:18 by omakbas          ###   ########.fr       */
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
	// Don't touch pipefd[0] - parent will handle it
	return (true);
}

bool	check_no_expand_for_heredoc(char *line, int i)
{
	if (line[i + 1] != '_' && (!ft_isalnum(line[i + 1]) || !line[i + 1]))
		return (false);
	return (true);
}
