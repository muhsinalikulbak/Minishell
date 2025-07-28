/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/28 20:05:24 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input_line(char *line)
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

void	main_loop(void)
{
	char	*line;

    while (true)
    {
        line = get_input(false);
        if (!line)
        {
            handle_eof();
            break;
        }
        if (g_signal_received == SIGINT)
        {
            g_signal_received = 0;
            free(line);
            continue ;
        }
        process_input_line(line);
        free(line);
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
