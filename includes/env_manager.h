/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:19 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/26 17:42:13 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MANAGER_H
# define ENV_MANAGER_H


typedef struct s_node
{
	char			*content;
    char            *key;
	struct s_node	*next;
}	t_map;


t_map	*create_map(char *key, char *content);
void	ft_map_add_back(t_map **map, t_map *new);
t_map	*ft_maplast(t_map *map);
int	    ft_mapsize(t_map *map);
void    print_map(t_map *map);
t_map   *mat_to_map(char **mat);
void    free_map(t_map *map);
bool is_key_exist(t_map *env_list, char* key);

#endif