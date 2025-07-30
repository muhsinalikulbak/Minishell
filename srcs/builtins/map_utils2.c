/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:19:46 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/28 14:22:39 by kayraakbas       ###   ########.fr       */
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

bool	is_key_exist(t_map *env_list, char *key)
{
	t_map	*ptr;

	ptr = env_list;
	while (ptr)
	{
		if (ft_strcmp(ptr->key, key) == 0)
			return (true);
		ptr = ptr->next;
	}
	return (false);
}

char	*try_get_value(char *key)
{
	t_map	*env;

	env = get_env_map(NULL);
	while (env)
	{
		if (str_equal(env->key, key))
			return (env->content);
		env = env->next;
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
			head = create_map(key, content);
		else
		{
			tmp = create_map(key, content);
			ft_map_add_back(&head, tmp);
		}
		i++;
	}
	return (head);
}

t_map	*create_map(char *key, char *content)
{
	t_map	*new_node;

	new_node = malloc(sizeof(t_map));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->key = key;
	new_node->next = NULL;
	return (new_node);
}
