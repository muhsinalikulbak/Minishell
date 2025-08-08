/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 22:39:34 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/08 16:53:12 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_builtin_cmd(char *cmd)
{
	if (str_equal(cmd, "cd"))
		return (true);
	if (str_equal(cmd, "echo"))
		return (true);
	if (str_equal(cmd, "pwd"))
		return (true);
	if (str_equal(cmd, "export"))
		return (true);
	if (str_equal(cmd, "unset"))
		return (true);
	if (str_equal(cmd, "env"))
		return (true);
	if (str_equal(cmd, "exit"))
		return (true);
	return (false);
}

bool	find_cmd(t_segment *segments)
{
	int		i;
	char	*full_path;
	char	*cmd;

	i = 0;
	full_path = try_get_value("PATH");
	while (i < segments->segment_count)
	{
		if (segments[i].args)
		{
			cmd = segments[i].args[0];
			if (is_builtin_cmd(cmd))
				segments[i].cmd_type = CMD_BUILTIN;
			else
			{
				if (!resolve_cmd_path(cmd, full_path, &segments[i]))
					return (false);
			}
		}
		i++;
	}
	return (true);
}
