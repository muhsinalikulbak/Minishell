/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/13 20:24:02 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_redir
{
	char			*filename;   // target file/ Burada char *delimiter için union kullanabilirim.
	int				heredoc_fd;  // heredocları açtıktan sonra tek pipe'de birden fazla heredoc var ise öncekini kapa değeri -1 yap
	t_token_state	state;		 // Burada filename'in state'i tutulacak. Örneğin "merhaba" ise DQ word olarak sayılacak.
	t_token_type	type;        // REDIR_IN, REDIR_OUT, etc.
	int				redir_count;
}		t_redir;

typedef struct s_segment
{
	char            **args;         // ["ls", "-la", NULL]
	t_redir         *redirections;  // linked list of redirections
	int				segment_count;
}		t_segment;


t_segment	*parser(t_token *token);
int			token_count_in_segment(t_token *token);
int			redir_count_in_segment(t_token *token);
int			get_segment_count(t_token *token);
bool		syntax_check(t_token *token);
void		free_segment(t_segment *segment, int end);
void		free_redir(t_redir *redir, int end);
t_token		*next_pipe(t_token *token);
bool		create_segment(t_token *token, t_segment *segments, int segment_count);
void		print_segment_list(t_segment *segments, int segment_count);
#endif
