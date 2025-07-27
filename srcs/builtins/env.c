/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/27 17:13:58 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Eğer export ile değişken eklendiyse ve değeri yoksa bu değişken env yazdırılırken yazılmacak.
// Bu flag koyarak yapılabilir.
void env(char **args, bool is_child)
{
	if (args[1])
	{
		ft_putendl_fd("env: too many arguments", 2);
		set_exit_code(2);
	}
	else
		print_map(get_env_map(NULL)); 
	set_exit_code(0);
}
