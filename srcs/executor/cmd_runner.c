/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_runner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:21:15 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/31 19:33:36 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_external(t_segment *segments)
{
	char	**env;

	env = create_env();
	if (!env)
		exit(EXIT_FAILURE);
	if (execve(segments->cmd_path, segments->args, env) == -1)
	{
		perror(segments->args[0]);
		if (errno == EACCES)
			exit(126);
		if (errno == ENOENT)
			exit(127);
		exit(EXIT_FAILURE);
	}
}

void	execute_builtin(t_segment *segments, bool is_child)
{
	char	*cmd;
	t_map	*env_map;
	
	(void)(is_child);
	// unset eklenicek, export düzeltilecek, cd home ayarlanacak.
	env_map = get_env_map(NULL);
	cmd = segments->args[0];
	if (str_equal(cmd, "cd"))
		cd(segments->args, &env_map);
	else if (str_equal(cmd, "echo"))
		echo(segments->args, STDOUT_FILENO);
	else if (str_equal(cmd, "pwd"))
		pwd();
	else if (str_equal(cmd, "export"))
		export(&env_map, segments->args[1], segments->args[2], false);
	else if (str_equal(cmd, "env"))
		env(segments->args);
	else if (str_equal(cmd, "exit"))
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
		ft_putstr_fd(segment->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		// FREE
		exit(127);
	}
	else if (segment->cmd_type == IS_A_DIRECTORY)
	{
		ft_putstr_fd(segment->args[0], 2);
		ft_putendl_fd(": Is a directory", 2);
		// FREE
		exit(126);
	}
	else if (segment->cmd_type == NO_PATH)
	{
		ft_putstr_fd(segment->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		// FREE
		exit(127);
	}
}
