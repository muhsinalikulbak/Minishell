/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/02 21:55:30 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{	
	(void) argc;
	(void) argv;
	char		*line;
	t_token		*token;
	//t_pipeline	pipelines; anlık olarak kullanılmıyor 
	t_map		*map;

	map = mat_to_map(env);
	print_map(map);
	cd("..", &map);
	print_map(map);
	free_map(map);
	while (true)
	{
		line = get_input();
		if (line && *line)
		{
			token = NULL;
			add_history(line); 
			if (!lexer(&token, line))
			{
				free(line);  // Add this to prevent memory leak
				continue ;
			}
			print_token_list(token);
			// pipelines.commands = parser(token);
			// if (pipelines.commands != NULL)
			// {
				
			// }
		}
        free_token(&token);
		free(line);  // Move this inside the loop to free each line
	}
}
