/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:39:34 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/01 20:09:47 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	find_builtin(char *cmd)
{
	if (str_equal(cmd, "cd"))
		return (true);
	if (str_equal(cmd, "echo"))
		return (true);
	if (str_equal(cmd, "pwd"))
		return (true);
	if (str_equal(cmd, "export"))
		return (true);
	if (str_equal(cmd, "unset"))
		return (true);
	if (str_equal(cmd, "env"))
		return (true);
	if (str_equal(cmd, "exit"))
		return (true);
	return (false);
}

static bool	path_access_control(char **full_path, char *slash_cmd, char **path)
{
	int		i;
	char	*cmd_with_path;

	i = 0;
	while (full_path[i])
	{
		cmd_with_path = ft_strjoin(full_path[i], slash_cmd);
		if (!cmd_with_path)
		{
			free_all(full_path);
			return (free(slash_cmd), false);
		}
		if (access(cmd_with_path, F_OK) == 0)
		{
			*path = cmd_with_path;
			free_all(full_path);
			return (free(slash_cmd), true);
		}
		free(cmd_with_path);
		i++;
	}
	free_all(full_path);
	*path = NULL;
	return (free(slash_cmd), true);
}

static bool	check_directory(t_segment *segment, char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		segment->cmd_path = ft_strdup(cmd);
		if (!segment->cmd_path)
			return (false);
		set_cmd_type(segment);
		return (true);
	}
	else
	{
		segment->cmd_path = NULL;
		segment->cmd_type = NO_PATH;
		return (true);
	}
}

static bool	find_path(char *cmd, char *env_path, t_segment *segment)
{
	char	**full_path;
	char	*slash_cmd;

	if (ft_strchr(cmd, '/'))
	{
		if (!check_directory(segment, cmd))
			return (false);
		return (true);
	}
	slash_cmd = ft_strjoin("/", cmd);
	if (!slash_cmd)
		return (false);
	full_path = ft_split(env_path, ':');
	if (!full_path)
		return (free(slash_cmd), false);
	if (!path_access_control(full_path, slash_cmd, &segment->cmd_path))
		return (false);
	if (segment->cmd_path)
		set_cmd_type(segment);
	return (true);
}

bool	find_cmd(t_segment *segments)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = try_get_value("PATH");
	while (i < segments->segment_count)
	{
		if (segments[i].args)
		{
			if (find_builtin(segments[i].args[0]))
				segments[i].cmd_type = CMD_BUILTIN;
			else if (full_path)
			{
				if (!find_path(segments[i].args[0], full_path, &segments[i]))
					return (false);
			}
			else
				segments[i].cmd_type = NO_PATH;
		}
		i++;
	}
	return (true);
}
