/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:21 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/28 20:25:03 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "builtins.h"
# include "parser.h"
// Forward declarations
typedef struct s_segment	t_segment;

bool	executor(t_segment *segments);
bool	open_pipefd(int pipefd[][2], int seg_count);
void	close_all_pipes(int pipefd[][2], int cmd_count);
void	pipe_setup(int pipefd[][2], int i, int cmd_count);
void	execute_builtin(t_segment *segments, bool is_child);
void	handle_command(t_segment *segment);
bool	process_setup(t_segment *segments, int *pids, int pipefd[][2]);
void	close_all_pipes(int pipefd[][2], int pipe_count);
bool	open_pipefd(int pipefd[][2], int pipe_count);
void	pipe_setup(int pipefd[][2], int i, int seg_count);
bool	handle_redirections(t_redir *redir);
#endif