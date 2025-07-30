/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:15:07 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/29 13:36:47 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_ambiguous(t_redir *redir)
{
	if (*redir->file_name == '\0' && redir->is_ambiguous)
	{
		ft_putendl_fd(":ambiguous redirect", 2);
		// FREE
		exit(EXIT_FAILURE);
	}
}

static void	open_redir_output(t_redir *redir)
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
		//FREE
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	open_redir_input(t_redir *redir)
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
			//FREE
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (type == HEREDOC)
	{
		dup2(redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
	}
}

void	handle_redirections(t_redir *redir)
{
	int				i;

	i = 0;
	while (i < redir->redir_count)
	{
		check_ambiguous(&redir[i]);
		if (redir[i].type == REDIR_IN || redir[i].type == HEREDOC)
			open_redir_input(&redir[i]);
		else if (redir[i].type == REDIR_OUT || redir[i].type == APPEND)
			open_redir_output(&redir[i]);
		i++;
	}
}
