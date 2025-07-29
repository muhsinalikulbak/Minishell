/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/29 02:05:34 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum e_cmd_type
{
	CMD_BUILTIN,
	CMD_EXTERNAL,
	CMD_NOT_FOUND,
	NO_PATH,
}	t_cmd_type;

typedef struct s_redir
{
	char			*file_name;
	int				heredoc_fd;
	t_token_state	state;
	t_token_type	type;
	int				redir_count;
	bool			is_ambiguous;
}		t_redir;

typedef struct s_segment
{
	char			**args;
	t_redir			*redirections;
	t_cmd_type		cmd_type;
	int				segment_count;
	char			*cmd_path;
}		t_segment;

t_segment	*parser(t_token *token);
int			token_count_in_segment(t_token *token);
int			redir_count_in_segment(t_token *token);
int			get_segment_count(t_token *token);
bool		syntax_check(t_token *token);
bool		free_segment(t_segment *segment, int end);
void		free_redir(t_redir *redir, int end);
t_token		*next_pipe(t_token *token);
bool		create_segment(t_token *token, t_segment *segments,
				int segment_count);
void		print_segment_list(t_segment *segments, int segment_count);
bool		check_no_expand_for_heredoc(char *line, int i);
void		write_pipefd(char *line, int pipefd[2]);
bool		heredoc_init(t_segment *segments);
bool		heredoc_finishing(char *line, int pipefd[2], int *fd);
void		print_heredoc_data(t_segment *segments);
void		heredoc_child_signal_setup(void);
void		heredoc_parent_signal_setup(void);
void		heredoc_restore_signals(void);
void		handle_heredoc_eof(char *delimiter, int pipefd[2]);
bool		heredoc_expand(char *line, int pipefd[2]);
char		*get_value_for_heredoc(char *line, int *i);
bool		heredoc_scan(t_redir *redir);
void		process_heredoc_line(char *line, int pipefd[2],
				bool is_it_expandable);
bool		heredoc_child_process(char *delimiter, int pipefd[2],
				bool is_it_expandable);
bool		find_cmd(t_segment *segments);
bool		heredoc_parent_process(int pipefd[2], pid_t child_pid, int *fd);
bool		heredoc(char *delimiter, int *fd, bool is_it_expandable);
#endif
