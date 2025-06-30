/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:37:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/30 22:17:17 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	str_equal(char *str1, char* str2)
{
	int	len1;
	int	len2;
	int	i;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 != len2)
		return (false);
	i = 0;
	while (i < len1)
	{
		if (str1[i] != str2[i])
			return (false);
		i++;
	}
	return (true);		
}

static int current_exit_code(int *exit_code)
{
	static int	current;
	if (!exit_code)
		return (current);
	current = *exit_code;
	return (current);
}
void	set_exit_code(int status)
{
	current_exit_code(&status);
}
int	get_exit_code()
{
	return (current_exit_code(NULL));
}