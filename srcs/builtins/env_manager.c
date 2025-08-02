/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:20:07 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/03 01:46:43 by muhsin           ###   ########.fr       */
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

char**	create_env()
{
	t_map	**env_map_ptr;
	t_map	*map;
	char	**env;
	char	*temp;
	int		count;
	int		i;

	env_map_ptr = get_env_map(NULL);
	map = *env_map_ptr;
	
	// Sadece content'i olan değişkenleri say
	count = 0;
	t_map *temp_map = map;
	while (temp_map)
	{
		if (temp_map->content)
			count++;
		temp_map = temp_map->next;
	}
	
	if (!map || count == 0)
		return (NULL);
	env = malloc(sizeof(char *) * (count + 1));
	if (!env)
		return (NULL);
	set_null(env, count);
	i = 0;
	while (map && i < count)
	{
		if (map->content)  // Sadece content'i olan değişkenleri ekle
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
