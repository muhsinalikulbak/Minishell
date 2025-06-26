/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/26 10:26:32 by muhsin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_token		*token;
	t_pipeline	pipelines;

	(void)argc;
	(void)argv;
	signal_setup();
	while (true)
	{
		line = get_input();
		if (line && *line)
		{
			token = NULL;
			if (!lexer(&token, line))
				continue ;
			add_history(line); 
			print_list(token);
			free_token(&token);
			// pipelines.commands = parser(token);
			// if (pipelines.commands != NULL)
			// {
				
			// }
		}
	}
	free(line);
}
