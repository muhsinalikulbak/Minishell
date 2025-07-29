/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:27:55 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/29 14:24:35 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_args(char **args, int i, bool is_newline, int fd)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (is_newline)
		write(fd, "\n", 1);
	set_exit_code(0);
}

void	echo(char **args, int fd)
{
	bool	is_newline;
	int		i;
	int		j;

	i = 1;
	is_newline = true;
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '-' && ft_strlen(args[i]) > 1)
		{
			j++;
			while (args[i][j] && args[i][j] == 'n')
				j++;
		}
		if (!args[i][j])
			is_newline = false;
		else
			break ;
		i++;
	}
	write_args(args, i, is_newline, fd);
}
