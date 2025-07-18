/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 02:23:34 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/18 18:06:27 by muhsin           ###   ########.fr       */
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
		i++;
	}
	free(segment);
	return (false);
}
