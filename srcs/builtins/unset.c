/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/03 14:47:58 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_head_node(t_map *node)
{
	t_map	**map;

	map = get_env_map(NULL);
	*map = node->next;
	node->next->prev = NULL;
}

void	unset(char **args)
{
	t_map	**map;
	t_map	*node;
	int		i;

	map = get_env_map(NULL);
	i = 1;
	while (args[i])
	{
		node = try_get_key_value_pair(args[i]);
		if (node)
		{
			if (node->prev)
			{
				node->prev->next = node->next;
				if (node->next)
					node->next->prev = node->prev;
			}
			else if (node->next)
				remove_head_node(node);
			else
				*map = NULL;
			free_map_node(node);
		}
		i++;
	}
}
