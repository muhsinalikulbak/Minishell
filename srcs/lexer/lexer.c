/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:52:24 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/15 23:50:26 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void scan(char *input_cmd, t_token **token){
    // commmand matrix
    char **scanned_cmd;
    int arg;
    scanned_cmd = ft_split(input_cmd, ' '); // check for the memory leaks in here
    if (!scanned_cmd)
    {
        perror("command could not scanned");
        return;
    }
    arg = 0;
    while (scanned_cmd[arg])
    {
        if (anlayse(scanned_cmd[arg], token) == false)
        {
            printf("command not found: %s\n",scanned_cmd[arg]);
            break;
        }
        arg++;
    }
    arg = 0;
}

bool anlayse(char *cmd, t_token **token){
    char *token_value;
    t_token_type token_type;

    //syntax check
     if (cmd[0] == '|')
        token_type = TOKEN_PIPE;
    else if (cmd[0] == '<')
    {
        if (cmd[1] == '<')
            token_type = TOKEN_HEREDOC;
        else
            token_type = TOKEN_REDIR_IN;
    }
    else if (cmd[0] == '>')
    {
        if (cmd[1] == '>')
            token_type = TOKEN_APPEND;
        else
            token_type = TOKEN_REDIR_OUT;
    }
    else if (cmd[0] == '-')
        token_type = TOKEN_ARGUMENT;
    else
        token_type = TOKEN_COMMAND;

    token_value = cmd;        
    insert_token(token, token_value, token_type);
    return (true);
}

t_token *lexer(char *command_line){

    t_command command;
    t_token *token;

    token = NULL;
    scan(command_line, &token);

    int i = 0;
    
    return token;   
}