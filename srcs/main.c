/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/28 17:35:04 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_input_line(char *line)
{
	t_token		*token;
	t_segment	*segments;

	token = NULL;
	add_history(line);
	if (lexer(&token, line))
	{
		if (syntax_check(token))
		{
			segments = parser(token);
			if (segments)
			{
				executor(segments);
				free_segment(segments, segments->segment_count);
			}
		}
		else
			free_token(token);
	}
}

static void	main_loop(void)
{
	char	*line;

	while (true)
	{
		line = get_input(false);
		if (g_signal_received == SIGINT)
		{
			g_signal_received = 0;
			continue ;
		}
		if (line)
		{
			process_input_line(line);
			free(line);
		}
		else
			handle_eof();
	}
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	get_env_map(env);
	signal_setup();
	main_loop();
	return (0);
}
