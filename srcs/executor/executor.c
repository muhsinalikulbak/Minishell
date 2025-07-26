/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 01:29:56 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/26 14:42:42 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_segment *segments, bool is_child)
{
	char    *cmd;

	cmd = segments->args[0];
	if (str_equal(cmd, "cd"))
		cd(segments->args, get_env_map(NULL), is_child);
	if (str_equal(cmd, "echo"))
		echo(segments->args, STDOUT_FILENO, is_child);
	if (str_equal(cmd, "pwd"))
		pwd(is_child);
	if (str_equal(cmd, "export"))
		// export(get_env_map(),)
	if (str_equal(cmd, "unset"))
		// unset(get_env_map(),)
	if (str_equal(cmd, "env"))
		env(segments->args, is_child);
	if (str_equal(cmd, "exit"))
		ft_exit(segments->args);
}

void	handle_redirections(t_segment *segments)
{

}

void	executor(t_segment *segments)
{
	if (segments->segment_count == 1 && segments->is_builtin)
	{
		execute_builtin(segments, false);
		return ;
	}
	// Önce pipe'ları ayarla
	// Sonra segmentelere göre forkları at
	// her segmentin redirectonlarını ayarla
	// Ardından execute et
}
