/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:15:07 by mkulbak           #+#    #+#             */
/*   Updated: 2025/08/05 15:59:52 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_ambiguous(t_redir *redir, bool is_child)
{
	if (*redir->file_name == '\0' && redir->is_ambiguous)
	{
		ft_putendl_fd(":ambiguous redirect", 2);
		if (!is_child)
			return (false);
		cleanup_manager(EXIT_FAILURE);
	}
	return (true);
}

static bool	open_redir_output(t_redir *redir, bool is_child)
{
	t_token_type	type;
	int				fd;

	type = redir->type;
	if (type == REDIR_OUT)
		fd = open(redir->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (type == APPEND)
		fd = open(redir->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(redir->file_name);
		if (!is_child)
			return (false);
		cleanup_manager(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (true);
}

static bool	open_redir_input(t_redir *redir, bool is_child)
{
	t_token_type	type;
	int				fd;

	type = redir->type;
	if (type == REDIR_IN)
	{
		fd = open(redir->file_name, O_RDONLY, 0444);
		if (fd == -1)
		{
			perror(redir->file_name);
			if (!is_child)
				return (false);
			cleanup_manager(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (type == HEREDOC)
	{
		dup2(redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
	}
	return (true);
}

bool	handle_redirections(t_redir *redir, bool is_child)
{
	int		i;
	bool	check_error;

	i = 0;
	while (i < redir->redir_count)
	{
		check_error = check_ambiguous(&redir[i], is_child);
		if (redir[i].type == REDIR_IN || redir[i].type == HEREDOC)
			check_error = open_redir_input(&redir[i], is_child);
		else if (redir[i].type == REDIR_OUT || redir[i].type == APPEND)
			check_error = open_redir_output(&redir[i], is_child);
		if (!check_error)
		{
			set_exit_code(1);
			return (false);
		}
		i++;
	}
	set_exit_code(0);
	return (true);
}
