/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:17 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/29 12:39:30 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env_manager.h"

void	echo(char **args, int fd);
void	cd(char **args, t_map **env_map_head);
void	pwd(void);
void	export(t_map **env_map_head, char *var, char *key, bool is_set);// fonskiyon 4 argümandan fazla alıyo ve çok uzun
void	unset(t_map **env_map_head, char *key);
void	env(char **args);
void	ft_exit(char **args);
bool	validate_key(char *key);
void	add_new_var(t_map **env_map_head, char *key, char *var);
void	print_export(t_map **env_map_head, int size);
int		ft_strcmp(char *s1, char *s2);
void	free_map_node(t_map *node);
bool	update_existing_var(t_map **env_map_head, char *key, char *var);
bool	is_key_in_array(char **array, char *key);
void	free_mat(char **mat, int size);
#endif