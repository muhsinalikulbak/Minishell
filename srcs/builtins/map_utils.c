/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:14:24 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/08/07 18:06:34 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_map_add_back(t_map **map, t_map *new)
{
	t_map	*last;

	if (!new)
		return ;
	last = ft_maplast(*map);
	if (!last)
	{
		*map = new;
		new->prev = NULL;
		return ;
	}
	last->next = new;
	new->prev = last;
}

t_map	*ft_maplast(t_map *map)
{
	if (!map)
		return (NULL);
	while (map->next != NULL)
	{
		map = map->next;
	}
	return (map);
}

int	ft_mapsize(t_map *map)
{
	int	count;

	count = 0;
	while (map != NULL)
	{
		count++;
		map = map->next;
	}
	return (count);
}

void	free_map(t_map *map)
{
	t_map	*current;
	t_map	*next;

	if (!map)
	{
		printf("Empty token map\n");
		return ;
	}
	current = map;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		if (current->key)
			free(current->key);
		free(current);
		current = next;
	}
}
