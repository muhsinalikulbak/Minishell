/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/04 10:52:56 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	cd_control(char **args)
{
	if (!args)
		return (false);
	
	// args[1] boş string ise (sadece space varsa) ignore et
	if (args[1] && args[1][0] == '\0')
		args[1] = NULL;
	
	// args[2] kontrolü - args[1] varsa args[2]'ye bakabiliriz
	if (args[1] && args[2] && args[2][0] != '\0')
	{
		ft_putendl_fd("cd: too many arguments\n", 2);
		set_exit_code(1);
		return (false);
	}
	
	return (true);
}

static void	set_pwd_and_oldpwd(char *old_pwd, t_map **env_map_head)
{
	char	*pwd;

	update_key_value(env_map_head, "OLDPWD", old_pwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putendl_fd("memory allocation failed", 2);
		return ;
	}
	update_key_value(env_map_head, "PWD", pwd);
	set_exit_code(0);
}

void	cd(char **args, t_map **env_map_head)
{
	char	*old_pwd;
	char	*target_dir;

	if (!cd_control(args))
		return ;
	
	if (!args[1] || (args[1] && str_equal(args[1], "~")))
	{
		target_dir = getenv("HOME");
		if (!target_dir)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			set_exit_code(1);
			return ;
		}
	}
	else
		target_dir = args[1];
	
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("getcwd");
		return ;
	}
	
	if (chdir(target_dir) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(target_dir);
		set_exit_code(1);
		free(old_pwd);
		return ;
	}
	set_pwd_and_oldpwd(old_pwd, env_map_head);
}
