/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:45:19 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/18 18:07:39 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_pipefd(char *line, int pipefd[])
{
	write(pipefd[1], line, ft_strlen(line));
	write(pipefd[1], "\n", 1);
	free(line);
}

bool	heredoc_finishing(char *line, int pipefd[], int *fd)
{
	free(line);
	close(pipefd[1]);
	*fd = pipefd[0];
	return (true);
}

bool	check_no_expand_for_heredoc(char *line, int i)
{
	if (line[i + 1] != '_' && (!ft_isalnum(line[i + 1]) || !line[i + 1]))
		return (false);
	return (true);
}
