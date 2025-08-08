/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:48:22 by mkulbak           #+#    #+#             */
/*   Updated: 2025/08/08 16:49:29 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	search_in_path_dirs(char **full_path, char *slash_cmd, char **path)
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

static bool	resolve_absolute_path(t_segment *segment, char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		segment->cmd_path = ft_strdup(cmd);
		if (!segment->cmd_path)
			return (false);
		set_cmd_type(segment);
	}
	else
	{
		segment->cmd_path = NULL;
		segment->cmd_type = NO_PATH;
	}
	return (true);
}

static bool	resolve_cmd_in_path(char *cmd, char *env_path, t_segment *segment)
{
	char	**full_path;
	char	*slash_cmd;

	slash_cmd = ft_strjoin("/", cmd);
	if (!slash_cmd)
		return (false);
	full_path = ft_split(env_path, ':');
	if (!full_path)
		return (free(slash_cmd), false);
	if (!search_in_path_dirs(full_path, slash_cmd, &segment->cmd_path))
		return (false);
	if (segment->cmd_path)
		set_cmd_type(segment);
	return (true);
}

bool	resolve_cmd_path(char *cmd, char *env_path, t_segment *segment)
{
	if (ft_strchr(cmd, '/'))
	{
		if (!resolve_absolute_path(segment, cmd))
			return (false);
	}
	else if (env_path)
	{
		if (!resolve_cmd_in_path(cmd, env_path, segment))
			return (false);
	}
	else
	{
		segment->cmd_path = NULL;
		segment->cmd_type = NO_PATH;
	}
	return (true);
}
