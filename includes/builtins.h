/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:17 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/01 19:25:50 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "env_manager.h"


void echo(char *str);
void cd(char *path);
void pwd(char *pwd);
void export(t_map **env_map_head, char *var, char *key, bool is_set);
void ft_unset(t_map **env_map_head, char *key);
void ft_env(t_map *map);
void ft_exit();



#endif