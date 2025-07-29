/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:15:07 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/29 03:53:43 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fds(int *fds, int i)
{
	while (i >= 0)
	{
		close(fds[i]);
		i--;
	}
	free(fds);
}

static void	check_ambiguous(t_redir *redir, int *fds, int i)
{
	if (*redir->file_name == '\0' && redir->is_ambiguous)
	{
		ft_putendl_fd("ambiguous redirect", 2);
		close_fds(fds, i);
		exit(EXIT_FAILURE);
	}
}

static void	open_redir_output(int *fds, int i, t_redir *redir)
{
	t_token_type	type;

	type = redir->type;
	if (type == REDIR_OUT)
		fds[i] = open(redir->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (type == APPEND)
		fds[i] = open(redir->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fds[i] == -1)
	{
		perror(redir->file_name);
		close_fds(fds, i - 1);
		exit(EXIT_FAILURE);
	}
	dup2(fds[i], STDOUT_FILENO);
	close(fds[i]);
}

static void	open_redir_input(int *fds, int i, t_redir *redir)
{
	t_token_type	type;

	type = redir->type;
	if (type == REDIR_IN)
	{
		fds[i] = open(redir->file_name, O_RDONLY, 0444);
		if (fds[i] == -1)
		{
			perror(redir->file_name);
			close_fds(fds, i - 1);
			exit(EXIT_FAILURE);
		}
		dup2(fds[i], STDIN_FILENO);
		close(fds[i]);
	}
	else if (type == HEREDOC)
	{
		dup2(redir->heredoc_fd, STDIN_FILENO);
		close(redir->heredoc_fd);
	}
}

bool	handle_redirections(t_redir *redir)
{
	int				i;
	int				*fds;

	fds = malloc(sizeof(int) * redir->redir_count);
	if (!fds)
		return (false);
	i = 0;
	while (i < redir->redir_count)
	{
		check_ambiguous(&redir[i], fds, i - 1);
		if (redir[i].type == REDIR_IN || redir[i].type == HEREDOC)
			open_redir_input(fds, i , &redir[i]);
		else if (redir[i].type == REDIR_OUT || redir[i].type == APPEND)
			open_redir_output(fds, i, redir);
		i++;
	}
	return (true);
}
