/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:06:55 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/08/06 18:22:18 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_map	*find_smallest_unprinted_key(t_map **env_map_head,
		char **printed_keys)
{
	t_map	*ptr;
	t_map	*smallest;

	smallest = NULL;
	ptr = *env_map_head;
	while (ptr)
	{
		if (!is_key_in_array(printed_keys, ptr->key)
			&& (!smallest || ft_strcmp(ptr->key, smallest->key) < 0))
			smallest = ptr;
		ptr = ptr->next;
	}
	return (smallest);
}

static void	print_and_track_key(t_map *map, char **printed_keys, int index)
{
	if (map)
	{
		printf("declare -x %s", map->key);
		if (map->content)
			printf("=\"%s\"\n", map->content);
		else
			printf("\n");
		printed_keys[index] = ft_strdup(map->key);
	}
}

void	print_export(t_map **env_map_head, int size)
{
	t_map	*smallest;
	char	**printed_keys;
	int		i;

	i = 0;
	printed_keys = (char **)ft_calloc((size + 1), sizeof(char *));
	smallest = NULL;
	if (!printed_keys)
		return ;
	while (i < size)
	{
		smallest = find_smallest_unprinted_key(env_map_head, printed_keys);
		print_and_track_key(smallest, printed_keys, i);
		i++;
	}
	free_mat(printed_keys, size);
	set_exit_code(0);
}
