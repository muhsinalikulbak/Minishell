/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_runner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:21:15 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/27 16:18:54 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_external(t_segment *segments)
{
	if (segments->cmd_type == CMD_EXTERNAL)
	{
		if (!execve(segments->cmd_path, segments->args, NULL));
		{
			// Her şeyi free'le
			perror(segments->args[0]);
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
				exit(127);
		}
	}	
}

void	execute_builtin(t_segment *segments, bool is_child)
{
	char    *cmd;
	t_map	*env_map;

	env_map = get_env_map(NULL);
	cmd = segments->args[0];
	if (str_equal(cmd, "cd"))
		cd(segments->args, &env_map, is_child);
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

void	handle_command(t_segment *segment)
{
	if (segment->cmd_type == CMD_BUILTIN)
		execute_builtin(segment, true);
	else if (segment->cmd_type == CMD_EXTERNAL)
		execute_external(segment);
	else if (segment->cmd_type == CMD_NOT_FOUND)
	{
		// Her şeyi free'le
		ft_putstr_fd(segment->args[0], 2);
		ft_putendl_fd(": command not found", 2);
    	exit(127);
	}
	else if (segment->cmd_type == NO_PATH)
	{
		// Her şeyi free'le
		ft_putstr_fd(segment->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
    	exit(127);
	}
}
