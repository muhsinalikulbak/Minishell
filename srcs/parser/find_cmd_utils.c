/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 11:41:34 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/31 12:17:06 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_directory(char *path)
{
    struct stat	statbuf;

    if (stat(path, &statbuf) == 0)
        return (S_ISDIR(statbuf.st_mode));
    return (false);
}

void    set_cmd_type(t_segment *segment)
{
    if (segment->cmd_path == NULL)
        return ;
    if (is_directory(segment->cmd_path))
    {
        if (ft_strchr(segment->args[0], '/'))
            segment->cmd_type = IS_A_DIRECTORY;
    }
    else
        segment->cmd_type = CMD_EXTERNAL;
}
