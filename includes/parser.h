/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/16 01:05:36 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_big_command{
    int _numberOfAvailableSimpleCommands;
    int _numberOfSimpleCommands;
    t_command* _simpleCommands;
    t_io_redir io_redirection;
    /*
    int _background;
    static Command _currentCommand;
    static SimpleCommand* _currentSimpleCommand;
    */
} t_big_command;


// Parser Utils
t_big_command parser(t_token *token_list);
t_command *init_command_arr(t_command simple_command, int num_of_simple_cmds);
void prompt();
void print();
void execute();
void clear();
#endif