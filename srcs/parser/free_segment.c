/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:23:34 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/05 20:18:09 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir *redir, int end)
{
	int		i;

	i = 0;
	while (i < end)
	{
		if (redir[i].file_name)
			free(redir[i].file_name);
		if (redir[i].heredoc_fd != -1)
			close(redir[i].heredoc_fd);
		i++;
	}
	free(redir);
}

bool	free_segment(t_segment *segment, int end)
{
	int	i;

	i = 0;
	if (segment->pids)
		free(segment->pids);
	if (segment->pipefd)
		free(segment->pipefd);
	while (i < end)
	{
		if (segment[i].args != NULL)
			free_all(segment[i].args);
		if (segment[i].redirections)
			free_redir(segment[i].redirections,
				segment[i].redirections->redir_count);
		if (segment[i].cmd_path)
			free(segment[i].cmd_path);
		i++;
	}
	free(segment);
	return (false);
}
