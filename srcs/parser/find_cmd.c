/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:39:34 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/23 01:45:25 by muhsin           ###   ########.fr       */
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

static char	*path_access_control(char **full_path, char *slash_cmd)
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
			return (free(slash_cmd), NULL);
		}
		if (access(cmd_with_path, F_OK) == 0)
		{
			free_all(full_path);
			return (free(slash_cmd), cmd_with_path);
		}
		i++;
	}
	free_all(full_path);
	return (free(slash_cmd), NULL);
}

static char	*find_path(char *cmd, char *env_path)
{
	char	**full_path;
	char	*env_path;
	char	*slash_cmd;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	slash_cmd = ft_strjoin("/", cmd);
	if (!slash_cmd)
		return (NULL);
	full_path = ft_split(env_path, ':');
	if (!full_path)
		return (free(slash_cmd), NULL);
	return (path_access_control(full_path, slash_cmd));
}

// BUNA gerek olmayabilir. Direk ENV_PATH Olmadığı için cmd_path'i null yapıp command not found yollayabilirim.
bool	path_is_available(t_segment *segment)
{
	if (!try_get_value("PATH"))
	{
		if (access(segment->args[0], F_OK) == 0)
			segment->cmd_path = ft_strdup(segment->args[0]);
		segment->is_unset_env_path = false;
		return (false);
	}
	return (true);
}


// Builtin true ise builtindir
// Builtin değilse ve cmd_path NULL ise ama env_path varsa command not found
// Builtin değilse ve cmd_path NULL ise ve env_paty yok ise (yani false) No such file or directory
bool	find_cmd(t_segment *segments)
{
	int		i;
	char	*path;

	i = 0;
	while (i < segments->segment_count)
	{
		if (segments[i].args)
		{
			if (find_builtin(segments[i].args[0]))
				segments[i].is_builtin = true;
			else if (path_is_available(&segments[i]))
			{
				path = find_path(segments[i].args[0], try_get_value("PATH"));
				if (!path)
					return (false);
			}
		}
		i++;
	}
}
