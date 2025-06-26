/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/26 20:54:26 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_token		*token;
	t_pipeline	pipelines;
	t_map		*map;
	

	(void)argc;
	(void)argv;
	signal_setup();
	map = mat_to_map(env);
	export(&map, 0, 0, false);
	export(&map, "prova", NULL, true);
	export(&map, 0, 0, false);
	free(map);
	
	while (true)
	{
		line = get_input();  // Remove the 'true' parameter
		if (line && *line)
		{
			token = NULL;
			if (!lexer(&token, line))
			{
				free(line);  // Add this to prevent memory leak
				continue ;
			}
			add_history(line); 
			print_token_list(token);
			free_token(&token);
			// pipelines.commands = parser(token);
			// if (pipelines.commands != NULL)
			// {
				
			// }
		}
		free(line);  // Move this inside the loop to free each line
	}
}
