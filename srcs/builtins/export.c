/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/26 21:24:57 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_var(t_map **env_map_head, char *key, char *var)
{
    if (update_existing_var(env_map_head, key, var))
        return;
    
    if (!key)
    {
        printf("bash: %s not found\n", var);
        set_exit_code(130);
        return;
    }
    
    if (!validate_key(key))
    {
        printf("bash: export: '%s': not a valid identifier\n", key);
        set_exit_code(130);
        return;
    }
    
    add_new_var(env_map_head, key, var);
}

// export args'yi alıcak, çünkü birden fazla değişken eklenebilir ya da değişkenle birlikte değerleri de eklenebilir >>>> "export a b  c=3 e f=4 gibi"
// export türkçe karakteri variable olarak almıyor bu kontrol de yapılacak.
// is_child true olursa işlem bittikten sonra  ya da çıkıştan hemen önce segment ve t_map freelenecek.
void export(t_map **env_map_head, char *var, char *key, bool is_set, bool is_child)
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
