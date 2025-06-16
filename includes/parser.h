/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/17 01:17:35 by muhsin           ###   ########.fr       */
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

typedef struct s_redir
{
	t_token_type	type;        // REDIR_IN, REDIR_OUT, etc.
	char            *filename;   // target file
	struct s_redir  *next;
}		t_redir;

typedef struct s_cmd
{
	char            **args;         // ["ls", "-la", NULL]
	t_redir         *redirections;  // linked list of redirections
	struct s_cmd    *next;          // next command in pipeline
}		t_cmd;

typedef struct s_pipeline
{
	t_cmd   *commands;      // first command in pipeline
	int     cmd_count;      // number of commands
}		t_pipeline;

t_pipeline		parser(t_token *token_list);
bool			syntax_check(t_token *token_list);
#endif
