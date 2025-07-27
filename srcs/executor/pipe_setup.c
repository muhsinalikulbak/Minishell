/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:18:50 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/27 14:30:16 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(int pipefd[][2], int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}

bool	open_pipefd(int pipefd[][2], int seg_count)
{
	int	i;

	i = 0;
		while (i < seg_count)
	{
		if (pipe(pipefd[i]) == -1)
		{
			// Açılan varsa close' yap; çünkü sonraki prompta gidicek. fd açık kalmasın
			// Burada sorun olursa çıkmaya gerek yok büyük ihtimal, prompt almaya devam edicek.
			return (false);
		}
		i++;
	}
	return (true);
}

void	setup_pipes(int pipefd[][2], int i, int cmd_count)
{
	if (i == 0)
		dup2(pipefd[i][1], STDOUT_FILENO);
	else if (i == cmd_count - 1)
		dup2(pipefd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(pipefd[i - 1][0], STDIN_FILENO);
		dup2(pipefd[i][1], STDOUT_FILENO);
	}
}
