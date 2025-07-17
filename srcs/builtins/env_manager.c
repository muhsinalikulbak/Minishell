/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:20:07 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/17 22:58:31 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*get_env_map(char **env)
{
	static t_map	*env_map = NULL;

	if (!env_map && env)
		env_map = mat_to_map(env);
	return (env_map);
}
