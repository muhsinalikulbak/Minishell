/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/27 17:31:10 by muhsin           ###   ########.fr       */
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

void	cd(char **args, t_map **env_map_head, bool is_child)
{   
	char *pwd;
	char *old_pwd;

	if (!cd_control(args))
		return ;
	old_pwd = getcwd(NULL, 0);
	// Eğer PWD ya da OLDPWD unset edildiyse herhangi bir güncelleme yapılmayacak.
	if (try_get_value("OLDPWD"))
		export(env_map_head, old_pwd, "OLDPWD", true, is_child); // Burada double free durumu olabilir. Dikkat et.
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (try_get_value("PWD"))
		export(env_map_head, pwd, "PWD", true, is_child); // Aynı şekilde burda da
	if (pwd)
		free(pwd);
	else
		ft_putendl_fd("error: getwcd", 2);
	set_exit_code(0);
}
