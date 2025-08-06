/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/08/06 10:49:07 by muhsin           ###   ########.fr       */
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
		free(line);
		if (syntax_check(token))
		{
			segments = parser(token);
			if (segments)
			{
				get_segments(segments);
				executor(segments);
				free_segment(segments, segments->segment_count);
			}
		}
		else
			free_token(token);
	}
	else
		free(line);
}

static void	input_loop(void)
{
	char	*line;

    while (true)
    {
		g_signal_received = 0;
        line = get_input(false);

        if (!line)
        {
            handle_eof();
            break;
        }
        if (ft_strlen(line) > 0)
        {
            process_input_line(line);
        }
    }
}

int	main(int argc, char **argv, char **env)
{
	t_map	**env_map_ptr;

	(void) argc;
	(void) argv;
	get_env_map(env);
	env_map_ptr = get_env_map(NULL);
	if (!env_map_ptr || !*env_map_ptr)
	{
		ft_putendl_fd("Memory allocation for env failed, try again", 2);
		exit(EXIT_FAILURE);
	}
	signal_setup();
	input_loop();
	return (0);
}
