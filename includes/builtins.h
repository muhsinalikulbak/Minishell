/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:17 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/30 14:18:42 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "env_manager.h"


void echo();
void cd();
void pwd();
void export(t_map **env_map_head, char *var, char *key, bool is_set);
void unset();
void ft_env(t_map *map);
//void exit();



#endif