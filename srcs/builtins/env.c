/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/03 01:23:30 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// değişken yoksa env de gözükmüyücek, ama export a=  olunca ve değer olunca env de gözüküyo
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
		print_map(*env_map_ptr);
	}
	set_exit_code(0);
}
