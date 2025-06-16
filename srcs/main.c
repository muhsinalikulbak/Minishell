/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/16 03:54:21 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_command	command;
	t_pipeline	pipelines;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		line = get_input();
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		command.cmd_head = lexer(line);
		pipelines = parser(command.cmd_head);
		print_list(command.cmd_head);
		free(line);
		free_list(&command.cmd_head);
	}
}
