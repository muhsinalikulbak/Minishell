/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:17 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/23 18:26:19 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "env_manager.h"

void	write_echo(char **args, int i, bool is_newline, int fd);
void	echo(char **args, int fd);
void	cd(char *path, t_map **env_map_head);
void	pwd(char *pwd);
void	export(t_map **env_map_head, char *var, char *key, bool is_set);
void	unset(t_map **env_map_head, char *key);
void	env(void);
void    ft_exit(char **args);

void set_var(t_map **env_map_head, char *key, char *var);
void print_export(t_map **env_map_head, int size);
int	ft_strcmp(char *s1, char *s2);
void free_map_node(t_map *node);
bool update_existing_var(t_map **env_map_head, char *key, char *var);
bool is_key_in_array(char **array, char *key);
void free_mat(char **mat, int size);
#endif