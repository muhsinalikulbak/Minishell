/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/13 15:11:09 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* 
// Command Data Structure  
// Describes a simple command and arguments 
struct SimpleCommand{
    // Available space for arguments currently preallocate;
	int _numberOfAvailableArguments;
    // Number of argument;
	int _numberOfArguments;
    // Array of argument;
	char** _arguments; 
	SimpleCommand();
	void insertArgument(char* argument);
};
    // Describes a complete command with the multiple pipes if any 
    // and input/output redirection if any. 

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


#endif