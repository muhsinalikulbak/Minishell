/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/01 22:03:03 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_var(t_map **env_map_head, char *key, char *var)
{
	if (update_existing_var(env_map_head, key, var))
		return ;
	if (!key)
	{
		printf("%s not found\n", var);
		set_exit_code(130);
		return ;
	}
	if (!validate_key(key))
	{
		printf("export: '%s': not a valid identifier\n", key);
		set_exit_code(130);
		return ;
	}
	add_new_var(env_map_head, key, var);
}

// değişken yoksa env de gözükmüyücek, ama export a=  olunca ve değer olunca env de gözüküyo

void	export(t_map **env_map_head, char *var, char *key, bool is_set)
{
	int	size;

	if (!env_map_head || !*env_map_head)
		return ;
	size = ft_mapsize(*env_map_head);
	if (is_set)
		set_var(env_map_head, key, var);
	else
		print_export(env_map_head, size);
}
