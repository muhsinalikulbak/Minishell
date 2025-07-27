/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/27 03:20:35 by muhsin           ###   ########.fr       */
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
	
	get_env_map(env); // İlk çağrıda env'i oluştur ve static'de sakla
	signal_setup();
	
	while (true)
	{
		line = get_input(false);
		
		if (g_signal_received == SIGINT)
        {
            g_signal_received = 0;
            continue;
        }
		
		if (line)
		{
			token = NULL;
			add_history(line);
			if (lexer(&token, line)) // Lexerda syntax alırsa kendi içinde free_token yapıyor.
			{
				// print_token_list(token);
				if (syntax_check(token))
				{
					segments = parser(token);
					if (segments)
					{
						// print_segment_list(segments, segments->segment_count);
						// print_heredoc_data(segments);
						// pipe_lines NULL değilse executa'a gidicek.
						executor(segments);
						free_segment(segments, segments->segment_count);
					}
				}
				else
					free_token(token);
			}
			free(line);
		}
		else 
			handle_eof();
	}
}
