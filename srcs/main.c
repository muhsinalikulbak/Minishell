/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/21 22:00:24 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_pipeline	pipelines;
	t_token		*token;

	(void)argc;
	(void)argv;
	token = NULL;
	while (true)
	{
		line = get_input();
		if (line)
		{
			lexer(&token, line); 
			print_list(token);
			pipelines.commands = parser(token);
			if (pipelines.commands != NULL)
			{
				
			}
		}
		free(line);
	}
}
