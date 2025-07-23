/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/23 16:04:56 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_redir
{
	char			*filename;
	int				heredoc_fd;  // heredocları açtıktan sonra tek pipe'de birden fazla heredoc var ise öncekini kapa
	t_token_state	state;		 // Burada filename'in state'i tutulacak. Örneğin "merhaba" ise DQ word olarak sayılacak.
	t_token_type	type;        // REDIR_IN, REDIR_OUT, etc.
	int				redir_count;
	bool			is_ambiguous;
}		t_redir;

typedef struct s_segment
{
	char            **args;         // ["ls", "-la", NULL]
	t_redir         *redirections;  // array of redirections
	int				segment_count;
	char			*cmd_path;
	bool			is_builtin;
}		t_segment;


t_segment	*parser(t_token *token);
int			token_count_in_segment(t_token *token);
int			redir_count_in_segment(t_token *token);
int			get_segment_count(t_token *token);
bool		syntax_check(t_token *token);
bool		free_segment(t_segment *segment, int end);
void		free_redir(t_redir *redir, int end);
t_token		*next_pipe(t_token *token);
bool		create_segment(t_token *token, t_segment *segments, int segment_count);
void		print_segment_list(t_segment *segments, int segment_count);
bool		check_no_expand_for_heredoc(char *line, int i);
void		write_pipefd(char *line, int pipefd[]);
bool		heredoc_init(t_segment *segments);
bool		heredoc_finishing(char *line, int pipefd[], int *fd);
void		print_heredoc_data(t_segment *segments);
bool		find_cmd(t_segment *segments);
#endif
