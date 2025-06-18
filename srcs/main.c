/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/17 19:19:55 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_pipeline	pipelines;

	(void)argc;
	(void)argv;
	while (true)
	{
		line = get_input();
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		pipelines.commands = parser(lexer(line));
		if (pipelines.commands != NULL)
		{
			
		}
		free(line);
	}
}
