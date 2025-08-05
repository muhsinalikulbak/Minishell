/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/05 19:51:26 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_alpha(char **args)
{
	int	i;

	i = 0;
	while (args[1][i])
	{
		if (ft_isalpha(args[1][i]))
		{
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(":numeric argument required", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_many_arguments(char **args)
{
	if (args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		set_exit_code(1);
		return (false);
	}
	return (true);
}

void	ft_exit(char **args)
{
	int	exit_code;

	ft_putendl_fd("exit", 2);
	if (!args[1])
	{
		cleanup_manager(get_exit_code());
	}
	if (!check_alpha(args))
		cleanup_manager(get_exit_code());
	if (check_many_arguments(args))
	{
		exit_code = ft_atoi(args[1]);
		cleanup_manager(exit_code);
	}
}
