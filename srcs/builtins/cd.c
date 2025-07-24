/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/24 01:39:45 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cd(char **args, t_map **env_map_head)
{    
	char *pwd;
	char *old_pwd;

	if (!path)
	{
		printf("bash: cd: missing argument\n");
		return;
	}
	old_pwd = getcwd(NULL, 0);
	// Eğer PWD ya da OLDPWD unset edildiyse herhangi bir güncelleme yapılmayacak.
	export(env_map_head, old_pwd, "OLDPWD", true);
	if (chdir(path) == -1)
	{
		perror("bash: cd");
		return;
	}
	pwd = getcwd(NULL, 0);
	export(env_map_head, pwd, "PWD", true);
	if (pwd)
	{
		printf("current dir: %s\n", pwd);
		free(pwd);
	}
	else
		perror("bash: getcwd");
}
