/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:29:56 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/26 21:12:37 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_segment *segments, bool is_child)
{
	char    *cmd;
	t_map	*env_map;

	cmd = segments->args[0];
	if (str_equal(cmd, "cd"))
	{
		env_map = get_env_map(NULL);
		cd(segments->args, &env_map, is_child);
	}
	if (str_equal(cmd, "echo"))
		echo(segments->args, STDOUT_FILENO, is_child);
	if (str_equal(cmd, "pwd"))
		pwd(is_child);
	if (str_equal(cmd, "export"))
		export(&env_map, segments->args[1], segments->args[2], false, is_child);
	// if (str_equal(cmd, "unset"))
	// 	unset(&env_map, segments)
	if (str_equal(cmd, "env"))
		env(segments->args, is_child);
	if (str_equal(cmd, "exit"))
		ft_exit(segments->args);
}

void	handle_redirections(t_segment *segments)
{

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

bool	executor(t_segment *segments)
{
	int	pipefd[segments->segment_count - 1][2];
	int		i;
	pid_t	*pids;

	if (segments->segment_count == 1 && segments->is_builtin)
	{
		execute_builtin(segments, false);
		return (true);
	}
	if (!open_pipefd(pipefd, segments->segment_count - 1))
		return (false);
	pids = malloc(sizeof(pid_t) * segments->segment_count);
	if (!pids)
	{
		// close pipe yap
		return (false);
	}
	i = 0;
	while (i < segments->segment_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			// close pipe
			// Diğer processleri bekle
			return (false);
		}
		if (pids[i] == 0)
		{
			
		}
		i++;
	}
	

	
	// Sonra segmentelere göre forkları at
	// her segmentin redirectonlarını ayarla
	// Ardından execute et
	
	free(pids);
	return (true);
}
