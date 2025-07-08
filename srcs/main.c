/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/07 21:52:03 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_parser(t_map *env_map)
{
    printf("\n=== PARSER TEST CASES ===\n\n");
    
    char *test_cases[] = {
        "ls -la",
        "cat file.txt | grep test",
        "ls -la > output.txt",
        "cat < input.txt | sort > sorted.txt",
        "grep pattern file.txt >> results.txt",
        "echo hello << EOF",
        "ls -la | grep test | wc -l",
        "cat file1.txt file2.txt > combined.txt",
        NULL
    };
    
    for (int i = 0; test_cases[i]; i++)
    {
        printf("Test Case %d: \"%s\"\n", i + 1, test_cases[i]);
        printf("----------------------------------------\n");
        
        t_token *token = NULL;
        
        // Tokenize the input
        if (lexer(&token, test_cases[i], env_map))
        {
            printf("TOKENS:\n");
            print_token_list(token);
            printf("\n");
            
            // Parse the tokens
            t_cmd *parsed_commands = parser(token);
            if (parsed_commands)
            {
                printf("PARSED COMMANDS:\n");
                print_parser(parsed_commands);
                
                // Free parsed commands
                free_commands(parsed_commands);
            }
            else
            {
                printf("Parser failed or syntax error\n");
            }
            
            // Free tokens
            free_token(&token);
        }
        else
        {
            printf("Lexer failed\n");
        }
        
        printf("\n");
    }
}


int	main(int argc, char **argv, char **env)
{	
	(void) argc;
	(void) argv;

	char		*line;
	t_token		*token;

	t_map		*map;
	map = mat_to_map(env);
	signal_setup();

	// Çalışması için şimdilik yorum satrına alındı. ( MUHSİN )
	// printf("Running parser test cases...\n");
 //    test_parser(map);

	
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
