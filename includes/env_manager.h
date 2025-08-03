/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:19 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/03 13:13:26 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MANAGER_H
# define ENV_MANAGER_H

typedef struct s_node
{
	char			*content;
	char			*key;
	struct s_node	*next;
}	t_map;

t_map	*create_map_node(char *key, char *content);
void	ft_map_add_back(t_map **map, t_map *new);
t_map	*ft_maplast(t_map *map);
int		ft_mapsize(t_map *map);
void	print_map(t_map *map);
t_map	*mat_to_map(char **mat);
void	free_map(t_map *map);
char	*try_get_value(char *key);
t_map	*try_get_key_value_pair(char *key);
t_map	**get_env_map(char **env);
char**	create_env_for_execve();

#endif