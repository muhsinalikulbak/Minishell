/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/12 20:01:30 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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
bool		syntax_check(t_token *token);
t_segment	*get_last_segment(t_segment *segment);
void		segment_add_back(t_segment **segments, t_segment *segment);
int			token_count_in_segment(t_token *token);
int			redir_count_in_segment(t_token *token);
void		free_segments(t_segment *segments);
#endif
