/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:46:23 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/23 19:39:34 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *path, t_map **env_map_head)
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

void pwd(char *pwd)
{
	pwd = getcwd(NULL, 0);
	printf("%s\n",pwd);
	free(pwd);
}

// export args'yi alıcak, çünkü birden fazla değişken eklenebilir ya da değişkenle birlikte değerleri de eklenebilir >>>> "export a b  c=3 e f=4 gibi"
void export(t_map **env_map_head, char *var, char *key, bool is_set)
{
	int size;

	if (!env_map_head || !*env_map_head)
		return;

	size = ft_mapsize(*env_map_head);

	if(is_set)
		set_var(env_map_head, key, var);
	else
		print_export(env_map_head, size);
}

void unset(t_map **env_map_head, char *key)
{
	t_map *current;
	t_map *prev;

	if (!env_map_head || !*env_map_head || !key)
		return;

	current = *env_map_head;
	prev = NULL;

	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_map_head = current->next;
			free_map_node(current);
			printf("bash: unset: %s: successfully removed\n", key);
			return;
		}
		prev = current;
		current = current->next;
	}
	printf("bash: unset: %s: not found\n", key);
}

void env()
{
	print_map(get_env_map(NULL)); 
}

void ft_exit(char **args)
{
	exit(get_exit_code());
}
