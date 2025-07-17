/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/17 23:11:29 by muhsin           ###   ########.fr       */
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
		if (line)
		{
			token = NULL;
			add_history(line);
			if (lexer(&token, line)) // Lexerda syntax alırsa kendi içinde free_token yapıyor.
			{
				print_token_list(token);
                segments = parser(token);
                if (segments)
                {
                    print_segment_list(segments, segments->segment_count);
                    print_heredoc_data(segments);
                    // pipe_lines NULL değilse executa'a gidicek.
					free_segment(segments, segments->segment_count);
                }
				free_token(token);
			}
			free(line);
		}
	}
}
