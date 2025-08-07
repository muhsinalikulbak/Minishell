/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/07 18:05:32 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_map_for_env(t_map *map)
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
		if (ptr->content)
		{
			printf("%s=", ptr->key);
			printf("%s\n", ptr->content);
		}
		ptr = ptr->next;
	}
}

void	env(char **args)
{
	t_map	**env_map_ptr;

	if (args[1])
	{
		ft_putendl_fd("env: too many arguments", 2);
		set_exit_code(2);
	}
	else
	{
		env_map_ptr = get_env_map(NULL);
		print_map_for_env(*env_map_ptr);
		set_exit_code(0);
	}
}
