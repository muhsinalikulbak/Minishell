/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:17 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/24 22:09:45 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "env_manager.h"

void	echo(char **args, int fd, bool is_child);
void	cd(char **args, t_map **env_map_head, bool is_child);
void	pwd(char *pwd, bool is_child);
void	export(t_map **env_map_head, char *var, char *key, bool is_set, bool is_child);
void	unset(t_map **env_map_head, char *key, bool is_child);
void	env(bool is_child);
void	ft_exit(char **args);

// Export utils functions
bool	validate_key(char *key);
void	add_new_var(t_map **env_map_head, char *key, char *var);
void	print_export(t_map **env_map_head, int size);
int		ft_strcmp(char *s1, char *s2);
void	free_map_node(t_map *node);
bool	update_existing_var(t_map **env_map_head, char *key, char *var);
bool	is_key_in_array(char **array, char *key);
void	free_mat(char **mat, int size);
#endif