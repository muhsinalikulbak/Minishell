/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/22 01:28:37 by muhsin           ###   ########.fr       */
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
	while (true)
	{
		line = get_input();
		if (line)
		{
			token = NULL;
			lexer(&token, line); 
			print_list(token);
			// pipelines.commands = parser(token);
			// if (pipelines.commands != NULL)
			// {
				
			// }
		}
		free(line);
	}
}
