/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:41:34 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/07 18:33:06 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_a_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == 0)
		return (S_ISDIR(statbuf.st_mode));
	return (false);
}

void	set_cmd_type(t_segment *segment)
{
	if (is_a_directory(segment->cmd_path))
	{
		if (ft_strchr(segment->args[0], '/'))
			segment->cmd_type = IS_A_DIRECTORY;
	}
	else if (access(segment->cmd_path, X_OK) == 0)
		segment->cmd_type = CMD_EXTERNAL;
	else
		segment->cmd_type = PERMISSION_DENIED;
}
