/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:17 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/02 21:52:02 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "env_manager.h"


void echo(char *str);
void cd(char *path, t_map **env_map_head);
void pwd(char *pwd);
void export(t_map **env_map_head, char *var, char *key, bool is_set);
void ft_unset(t_map **env_map_head, char *key);
void ft_env(t_map *map);
void ft_exit();

void set_var(t_map **env_map_head, char *key, char *var);
void print_export(t_map **env_map_head, int size);
int	ft_strcmp(char *s1, char *s2);
void free_map_node(t_map *node);
bool update_existing_var(t_map **env_map_head, char *key, char *var);
bool is_key_in_array(char **array, char *key);
void free_mat(char **mat, int size);
#endif