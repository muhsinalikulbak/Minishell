/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/30 22:21:56 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_token		*token;
	//t_pipeline	pipelines; anlık olarak kullanılmıyor 
	//t_map		*map;
	

	(void)argc;
	(void)argv;
	(void)env;

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
