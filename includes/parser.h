/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/07 21:43:44 by omakbas          ###   ########.fr       */
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
	t_token_state	state;		 // Burada filename'in state'i tutulacak. Örneğin "merhaba" ise DQ word olarak sayılacak.
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


t_cmd	*parser(t_token *token_list);
bool	syntax_check(t_token *token_list);
void	print_parser(t_cmd *parsed_list);
t_cmd	*new_cmd(t_token *start, t_token *end);
char 	**create_arg_mat(int arg_count);
t_redir *create_redirection(t_token *redir_token, t_token *file_token);
void add_redirection_to_cmd(t_cmd *cmd, t_redir *redir);
void free_redirections(t_redir *redirections);
void print_redirections(t_redir *redirections);
int count_word_tokens(t_token *start, t_token *end);
bool is_redirection_token(t_token_type type);
void free_commands(t_cmd *commands);

#endif
