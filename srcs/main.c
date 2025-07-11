/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/12 02:01:59 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{	
	(void) argc;
	(void) argv;

	char		*line;
	t_token		*token;

	t_map		*map;
	map = mat_to_map(env);
	signal_setup();

	while (true)
	{
		line = get_input();
		if (line)
		{
			token = NULL;
			add_history(line); 
			if (!lexer(&token, line, map))
			{
				free(line);  // Add this to prevent memory leak
				continue ;
			}
			print_token_list(token);
			free_token(&token);

			free(line);  // Move this inside the loop to free each line
		}
	}
}
