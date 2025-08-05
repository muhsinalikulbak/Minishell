/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:43:22 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/08/05 19:45:26 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	free_mat(char **mat, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (mat[i])
			free(mat[i]);
		i++;
	}
	free(mat);
}

void	free_map_node(t_map *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->content)
		free(node->content);
	free(node);
}

bool	is_key_in_array(char **array, char *key)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], key) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	update_key_value(t_map **env_map_head, char *key, char *value)
{
	t_map	*node;

	node = try_get_key_value_pair(key);
	if (node)
	{
		if (node->content)
			free(node->content);
		node->content = value;
		return (true);
	}
	else
	{
		node = create_map_node(key, value);
		if (!node)
			return (false);
		ft_map_add_back(env_map_head, node);
	}
	return (true);
}
