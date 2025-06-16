/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/16 03:03:12 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_error_type
{
	SYNTAX_ERROR_PIPE_START,
	SYNTAX_ERROR_PIPE_END,
	SYNTAX_ERROR_CONSECUTIVE_PIPES,
	SYNTAX_ERROR_REDIR_NO_FILE,
	SYNTAX_ERROR_UNCLOSED_QUOTE,
	SYNTAX_ERROR_HEREDOC_NO_DELIM
}		t_error_type;

typedef struct s_big_command
{
	int			number_of_available_simple_commands;
	int			number_of_simple_commands;
	t_command	*simple_commands;
	t_io_redir	io_redirection;
	/*
	int _background;
	static Command _currentCommand;
	static SimpleCommand* _currentSimpleCommand;
    */
}		t_big_command;

// Parser Utils
t_big_command	parser(t_token *token_list);
t_command		*init_command_arr(t_command simple_command, int num_of_simple_cmds);
void			prompt(void);
void			print(void);
void			execute(void);
void			clear(void);
#endif
