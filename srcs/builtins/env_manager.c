/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:20:07 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/31 19:32:48 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*get_env_map(char **env)
{
	static t_map	*env_map = NULL;

	if (!env_map && env)
		env_map = mat_to_map(env);
	return (env_map);
}

static int	get_env_map_count()
{
	t_map	*map;
	int		count;

	map = get_env_map(NULL);
	count = 0;
	while (map != NULL)
	{
		map = map->next;
		count++;
	}
	return (count);
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

char**	create_env()
{
	t_map	*map;
	char	**env;
	char	*temp;
	int		count;
	int		i;

	map = get_env_map(NULL);
	count = get_env_map_count();
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	set_null(env, count);
	i = -1;
	while (++i < count)
	{
		temp = ft_strjoin(map->key, "=");
		if (!temp)
			return (free_all(env));
		env[i] = ft_strjoin(temp, map->content);
		free(temp);
		if (!env[i])
			return (free_all(env));
		map = map->next;
	}
	return (env);
}
