/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_runner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 02:21:15 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/05 19:46:56 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_external(t_segment *segments)
{
	char	**env;

	env = create_env_for_execve();
	if (!env)
	{
		ft_putendl_fd("Memory allocation failed", 2);
		cleanup_manager(EXIT_FAILURE);
	}
	if (execve(segments->cmd_path, segments->args, env) == -1)
	{
		free_all(env);
		perror(segments->args[0]);
		if (errno == EACCES)
			cleanup_manager(126);
		if (errno == ENOENT)
			cleanup_manager(127);
		cleanup_manager(EXIT_FAILURE);
	}
}

void	execute_builtin(t_segment *segments, bool is_child)
{
	char	*cmd;
	t_map	**env_map;
	
	env_map = get_env_map(NULL);
	cmd = segments->args[0];
	if (str_equal(cmd, "cd"))
		cd(segments->args, env_map);
	else if (str_equal(cmd, "echo"))
		echo(segments->args, STDOUT_FILENO);
	else if (str_equal(cmd, "unset"))
		unset(segments->args);
	else if (str_equal(cmd, "pwd"))
		pwd();
	else if (str_equal(cmd, "export"))
		export(segments->args);
	else if (str_equal(cmd, "env"))
		env(segments->args);
	else if (str_equal(cmd, "exit"))
		ft_exit(segments->args);
	if (is_child)
	{
		cleanup_manager(get_exit_code());
	}
}

static void	print_err_and_exit(char *cmd, char *message, int exit_code)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(message, 2);
	cleanup_manager(exit_code);
}

static void	handle_error(t_segment *segment)
{
	if (segment->cmd_type == CMD_NOT_FOUND)
	{
		print_err_and_exit(segment->args[0], ": command not found", 127);

	}
	else if (segment->cmd_type == IS_A_DIRECTORY)
	{
		print_err_and_exit(segment->args[0], ": Is a directory", 126);

	}
	else if (segment->cmd_type == NO_PATH)
	{
		print_err_and_exit(segment->args[0], ": No such file or directory", 127);

	}
	else if (segment->cmd_type == PERMISSION_DENIED)
	{
		print_err_and_exit(segment->args[0], ": Permission denied", 126);
	}
}

void	handle_command(t_segment *segment)
{
	if (segment->cmd_type == CMD_BUILTIN)
		execute_builtin(segment, true);
	else if (segment->cmd_type == CMD_EXTERNAL)
		execute_external(segment);
	else
		handle_error(segment);
}
