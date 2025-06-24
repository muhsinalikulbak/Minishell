/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/24 09:08:05 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_pipeline	pipelines;

	(void)argc;
	(void)argv;
	
	signal_setup();
	while (true)
	{
		line = get_input();
		if (line)
		{
			pipelines.commands = parser(lexer(line));
		}
		free(line);

	}
}
