/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/16 00:51:08 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int main (int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
    
    char *line;
    t_command command;
    t_big_command big_command;
   
    while (1)
    {
        line = get_input();
        if (!line){
            printf("exit\n");
            break;
        }
        command.cmd_head = lexer(line);
        big_command = parser(command.cmd_head);

        print_list(command.cmd_head);
        
        free(line);
        free_list(&command.cmd_head);
        
    }

    return 0;
}
