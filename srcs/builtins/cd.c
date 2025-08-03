/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/03 00:55:36 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	cd_control(char **args)
{
	if (!args[1])
	{
		ft_putendl_fd("bash: cd: missing argument\n", 2);
		set_exit_code(1);
		return (false);
	}
	else if (args[2])
	{
		ft_putendl_fd("cd: too many arguments\n", 2);
		set_exit_code(1);
		return (false);
	}
	return (true);
}

void	cd(char **args, t_map **env_map_head)
{
	char	*pwd;
	char	*old_pwd;

	if (!cd_control(args))
		return ;
	old_pwd = getcwd(NULL, 0);
	update_key_value(env_map_head, "OLDPWD", old_pwd);
	if (chdir(args[1]) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(args[1]);
		set_exit_code(1);
		return ;
	}
	pwd = getcwd(NULL, 0);
	update_key_value(env_map_head, "PWD", pwd);
	if (pwd)
		free(pwd);
	else
		ft_putendl_fd("error: getwcd", 2);
	set_exit_code(0);
}
