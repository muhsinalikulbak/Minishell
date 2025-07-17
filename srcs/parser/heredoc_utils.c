/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 02:45:19 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/17 03:01:57 by muhsin           ###   ########.fr       */
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
