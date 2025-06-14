/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:52:24 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/14 18:30:58 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void scan(char *input_cmd, t_command cmd){
    // commmand matrix
    char **scanned_cmd;
    int arg = 0;
    scanned_cmd = ft_split(input_cmd, ' ');
    
    while (scanned_cmd[arg])
    {
        if (anlayse(scanned_cmd[arg], cmd) == false)
        {
            printf("command not found: %s\n",scanned_cmd[arg]);
            break;
        }
        arg++;
    }
}

bool anlayse(char *cmd, t_command simple_cmd){
    t_token token;
    //syntax check
    if(ft_strncmp(cmd, "ls", ft_strlen(cmd)) == 0)
    {
        token.value = cmd;
        token.type = TOKEN_COMMAND;
        insert_Argument(token, simple_cmd);
        return (true);
    }
    else if (ft_strncmp(cmd, "cat", ft_strlen(cmd)) == 0)
    {
        return (true);
    }
    else if (ft_strncmp(cmd, "grep", ft_strlen(cmd)) == 0)
    {
        return (true);
    }
    else if (ft_strncmp(cmd, "-a", ft_strlen(cmd)) == 0)
    {
        token.value = cmd;
        token.type = TOKEN_ARGUMENT;
        insert_Argument(token, simple_cmd);
        return (true);
    }
    else if (ft_strncmp(cmd, "|", ft_strlen(cmd)) == 0)
    {
        token.value = cmd;
        token.type = TOKEN_PIPE;
        insert_Argument(token, simple_cmd);
        return (true);
    }
    else
    {
        return (false);
    }
    return (false);
}

void lexer(char *command_line){

    t_command command;
    scan(command_line, command);

    int i = 0;
  


    //syntax_chck(tokenized_cmd);

    

    //checks the comamnd based on grammar and tokenize the command
    // -> will use the string helpers in the libft
    // -> handles with using tokens utils function 
    //converts it to command structure
    //if there is a syntax error returns error
}