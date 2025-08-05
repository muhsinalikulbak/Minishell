/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:20:00 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/05 19:43:36 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	validate_key(char *key_with_value)
{
	int	i;

	i = 0;
	if (ft_isdigit(key_with_value[i]) || key_with_value[i] == '=')
	{
		ft_putstr_fd(key_with_value, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		return (false);
	}
	while (key_with_value[i] && key_with_value[i] != '=')
	{
		if (!ft_isalnum(key_with_value[i]) && key_with_value[i] != '_')
		{
			ft_putstr_fd(key_with_value, 2);
			ft_putendl_fd(": not a valid identifier", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	print_malloc_error(char *str)
{
	ft_putendl_fd("Memory allocation failed", 2);
	if (str)
		free(str);
	return (false);
}

static bool	extract_key_and_value(char **key, char **value, char *key_with_value)
{
	char	*equal_position;

	equal_position = ft_strchr(key_with_value, '=');
	if (equal_position)
	{
		*value = ft_strdup(equal_position + 1);
		if (!*value)
			return (print_malloc_error(NULL));
		*key = ft_substr(key_with_value, 0, equal_position - key_with_value);
		if (!*key)
			return (print_malloc_error(*value));
	}
	else
	{
		*value = NULL;
		*key = ft_strdup(key_with_value);
		if (!*key)
			return (print_malloc_error(NULL));
	}
	return (true);
}

static void	process_export_variables(t_map **env_map, char **args)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (args[i])
	{
		if (validate_key(args[i]))
		{
			if (!extract_key_and_value(&key, &value, args[i]))
				return ;
			update_key_value(env_map, key, value);
		}
		else
			set_exit_code(1);
		i++;
	}
}

void	export(char **args)
{
	t_map	**env_map;

	env_map = get_env_map(NULL);
	set_exit_code(0);
	if (!args[1])
		print_export(env_map, ft_mapsize(*env_map));
	else
	{
		process_export_variables(env_map, args);
	}
}
