/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/13 18:04:30 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int main (int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
    
    char *line;
   
    while (1)
    {
        line = get_input();

        if (!line){
            printf("exit\n");
            break;
        }
        if (*line)
            add_history(line);
        lexer(line);
            
        //implement the readline and input handeling int ipnut dir

        // create .bash_history file and store commands there
        
        //apply Lexer to split commands into tokens (lex)
        // -> lexer directory will tokenize the input
        
        //Build command table with Parser (yacc)
        //Note: Both lex and yacc are standard commands in UNIX
        //Provide a Command Table after thsoe implementations
        
        // comand grammar : cmd [arg]*   ​ [ | cmd [arg]* ]*    [ [> filename] [< filename] [ >& filename] [>> filename] [>>& filename] ]* [&]
        // syntax of grammar will be checked in parser part 
        // command table will be a SimpleCommand structs 
        // Wildcard and Envars COMEBACK TO THIS AFTER FİNİSHİNG THE COMMAND TABLE 
        // Executer will take the commmand table
        free(line);
    }

    return 0;
}
