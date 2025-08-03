/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:19:46 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/08/03 01:23:20 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_key_content(char *str, char **key, char **content)
{
	int	j;
	int	key_len;
	int	content_len;
	int	content_start;

	j = 0;
	while (str[j] != '=')
		j++;
	key_len = j;
	*key = ft_substr(str, 0, key_len);
	content_len = ft_strlen(str) - key_len - 1;
	content_start = key_len + 1;
	*content = ft_substr(str, content_start, content_len);
}

t_map	*try_get_key_value_pair(char *key)
{
	t_map	**env_map_ptr;
	t_map	*env_map;

	env_map_ptr = get_env_map(NULL);
	env_map = *env_map_ptr;
	while (env_map)
	{
		if (str_equal(env_map->key, key))
			return (env_map);
		env_map = env_map->next;
	}
	return (NULL);
}

char	*try_get_value(char *key)
{
	t_map	**env_map_ptr;
	t_map	*env_map;

	env_map_ptr = get_env_map(NULL);
	env_map = *env_map_ptr;
	while (env_map)
	{
		if (str_equal(env_map->key, key))
			return (env_map->content);
		env_map = env_map->next;
	}
	return (NULL);
}

t_map	*mat_to_map(char **mat)
{
	int		i;
	char	*key;
	char	*content;
	t_map	*head;
	t_map	*tmp;

	head = NULL;
	i = 0;
	while (mat[i])
	{
		extract_key_content(mat[i], &key, &content);
		if (!head)
			head = create_map_node(key, content);
		else
		{
			tmp = create_map_node(key, content);
			ft_map_add_back(&head, tmp);
		}
		i++;
	}
	return (head);
}

t_map	*create_map_node(char *key, char *value)
{
	t_map	*new_node;

	new_node = malloc(sizeof(t_map));
	if (!new_node)
		return (NULL);
	new_node->content = value;
	new_node->key = key;
	new_node->next = NULL;
	return (new_node);
}
