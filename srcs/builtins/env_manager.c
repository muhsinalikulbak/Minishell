/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:20:07 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/07 18:15:00 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	**get_env_map(char **env)
{
	static t_map	*env_map = NULL;

	if (!env_map && env)
		env_map = mat_to_map(env);
	return (&env_map);
}

static void	set_null(char **env, int count)
{
	int	i;

	i = 0;
	while (i <= count)
	{
		env[i] = NULL;
		i++;
	}
}

int	get_env_map_count(void)
{
	t_map	*map;
	int		count;

	map = *(get_env_map(NULL));
	count = 0;
	while (map)
	{
		if (map->content)
			count++;
		map = map->next;
	}
	return (count);
}

static char	**set_env_for_execve(char **env, int count, t_map *map)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < count)
	{
		if (map->content)
		{
			temp = ft_strjoin(map->key, "=");
			if (!temp)
				return (free_all(env));
			env[i] = ft_strjoin(temp, map->content);
			free(temp);
			if (!env[i])
				return (free_all(env));
			i++;
		}
		map = map->next;
	}
	return (env);
}

char	**create_env_for_execve(void)
{
	t_map	*map;
	char	**env;
	int		count;

	map = *(get_env_map(NULL));
	count = get_env_map_count();
	if (count == 0)
		return (NULL);
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	set_null(env, count);
	if (!set_env_for_execve(env, count, map))
		return (NULL);
	return (env);
}
