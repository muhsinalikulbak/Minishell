/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/14 14:01:02 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{	
	(void) argc;
	(void) argv;

	char		*line;
	t_token		*token;
    t_segment	*segments;
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
			if (lexer(&token, line, map)) // Lexerda syntax alırsa kendi içinde free_token yapıyor.
			{
				print_token_list(token);
                segments = parser(token);
                if (segments)
                {
                    print_segment_list(segments, segments->segment_count);
                    // pipe_lines NULL değilse executa'a gidicek.
					free_segment(segments, segments->segment_count);
                }
                // Yoksa çıkıcak
                free_token(&token); // Parser'den geçsede geçmese de free_token yapılmalı.
			}
			free(line);
		}
	}
}
