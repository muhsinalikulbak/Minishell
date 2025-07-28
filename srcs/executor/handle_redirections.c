/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:15:07 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/28 21:01:27 by mkulbak          ###   ########.fr       */
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

static bool	file_check(t_redir *redir)
{
	if (*redir->filename == '\0' && redir->is_ambiguous)
	{
		ft_putendl_fd("ambiguous redirect", 2);
		return (false);
	}
	//*************************** */
	// Open bu hatayı yakalarsa burayı sil
	//*************************** */
	// if (*redir->filename == '\0')
	// {
	// 	// bash: fşke,: No such file or directory
	// 	ft_putendl_fd("bash: fşke,: No such file or directory")		
	// }
}

bool	handle_redirections(t_redir *redir)
{
	int		i;
	int		*fds;

	fds = malloc(sizeof(int) * redir->redir_count);
	if (!fds)
		return (false);
	i = 0;
	while (i < redir->redir_count)
	{
		if (!check_file(&redir[i]), fds)
		{
			close_fds(fds, i - 1);
			return (false);
		}
		if (redir[i].type == TOKEN_REDIR_IN || redir[i].type == TOKEN_HEREDOC)
		{

		}
	}
}
