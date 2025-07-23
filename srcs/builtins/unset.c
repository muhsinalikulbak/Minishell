/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/24 01:20:00 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void unset(t_map **env_map_head, char *key)
{
	t_map *current;
	t_map *prev;

	if (!env_map_head || !*env_map_head || !key)
		return;

	current = *env_map_head;
	prev = NULL;

	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_map_head = current->next;
			free_map_node(current);
			printf("bash: unset: %s: successfully removed\n", key);
			return;
		}
		prev = current;
		current = current->next;
	}
	printf("bash: unset: %s: not found\n", key);
}
