/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/24 20:50:01 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int argc, char **argv, char **env)
{
	char		*history;
	char		*line;
	t_token		*token;
	t_pipeline	pipelines;

	(void)argc;
	(void)argv;
	
	signal_setup();
	while (true)
	{
		line = get_input(true);
		if (line && *line)
		{
			token = NULL;
			history = lexer(&token, line);
			add_history(history); 
			print_list(token);
			free_list(&token);
			// pipelines.commands = parser(token);
			// if (pipelines.commands != NULL)
			// {
				
			// }
		}
	}
	free(line);
	free(history);
}
