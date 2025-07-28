/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:23:34 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/28 15:22:19 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir *redir, int end)
{
	int		i;

	i = 0;
	while (i < end)
	{
		if (redir[i].filename)
			free(redir[i].filename);
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
