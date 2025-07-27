/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:18:50 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/27 16:06:53 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(int pipefd[][2], int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close_pipefd(pipefd[i]);
		i++;
	}
}

bool	open_pipefd(int pipefd[][2], int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipefd[i]) == -1)
		{
			while (--i >= 0)
			{
				close_pipefd(pipefd[i]);
			}
			return (false);
		}
		i++;
	}
	return (true);
}

void	pipe_setup(int pipefd[][2], int i, int seg_count)
{
	if (i == 0)
		dup2(pipefd[i][1], STDOUT_FILENO);
	else if (i == seg_count - 1)
		dup2(pipefd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(pipefd[i - 1][0], STDIN_FILENO);
		dup2(pipefd[i][1], STDOUT_FILENO);
	}
}
