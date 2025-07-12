/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/12 13:46:58 by muhsin           ###   ########.fr       */
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
	t_redir 		*next;
	char			*filename;   // target file
	int				heredoc_fd;  // heredocları açtıktan sonra tek pipe'de birden fazla heredoc var ise öncekini kapa değeri -1 yap
	t_token_state	state;		 // Burada filename'in state'i tutulacak. Örneğin "merhaba" ise DQ word olarak sayılacak.
	t_token_type	type;        // REDIR_IN, REDIR_OUT, etc.
}		t_redir;

typedef struct s_segment
{
	char            **args;         // ["ls", "-la", NULL]
	t_redir         *redirections;  // linked list of redirections
	t_segment		*next;          // next command in pipeline
}		t_segment;


t_segment	*parser(t_token *token);
bool	syntax_check(t_token *token);

#endif
