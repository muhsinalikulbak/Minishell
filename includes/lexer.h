/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:23 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/14 18:30:48 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_token_type{
    TOKEN_COMMAND,
    TOKEN_COMMENT,
    TOKEN_ARGUMENT,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_EOF
}t_token_type; 

typedef struct s_token{
    char *value;
    t_token_type type;

} t_token;

typedef struct s_simple_command{
	int number_of_available_arguments;
	int number_of_arguments;
	t_token** args; 
} t_command;

/*
struct Command {
    int _numberOfAvailableSimpleCommands;
    int _numberOfSimpleCommands;
    SimpleCommand** _simpleCommands;
    char *_outFile;
    char *_inputFile;
    char *_errFile;
    int _background;
    void prompt();
    void print();
    void execute();
    void clear();
    Command();
    void insertSimpleCommand(SimpleCommand* simpleCommand);
    static Command _currentCommand;
    static SimpleCommand* _currentSimpleCommand;
};
*/

void lexer(char *command_line);
void syntax_chck(char **tokenized_cmd);
void scan(char *input_cmd, t_command cmd);
bool anlayse(char *cmd, t_command simple_cmd);
void insert_Argument(t_token token, t_command cmd);
#endif