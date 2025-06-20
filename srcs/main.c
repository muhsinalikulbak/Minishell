/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/20 00:17:26 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_pipeline	pipelines;

	(void)argc;
	(void)argv;
	while (true)
	{
		line = get_input();
		if (line)
		{
			pipelines.commands = parser(lexer(line));
			if (pipelines.commands != NULL)
			{
				
			}
		}
		free(line);
	}
}
