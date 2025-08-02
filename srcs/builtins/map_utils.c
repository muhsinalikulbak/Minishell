/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:14:24 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/08/03 01:48:07 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_map_add_back(t_map **map, t_map *new)
{
	t_map	*last;

	last = ft_maplast(*map);
	if (!last)
	{
		*map = new;
		return ;
	}
	last->next = new;
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

void	print_map(t_map *map)
{
	t_map	*ptr;

	if (!map)
	{
		printf("Empty token map\n");
		return ;
	}
	ptr = map;
	while (ptr)
	{
		if (ptr->content)  // NULL kontrol eklendi
		{
			printf("%s=", ptr->key);
			printf("%s\n", ptr->content);
		}
		ptr = ptr->next;
	}
	printf("\n");
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
		free(current->content);
		free(current->key);
		free(current);
		current = next;
	}
}
