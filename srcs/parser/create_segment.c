/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_segment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:10:19 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/08/09 00:41:32 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	set_redir(t_token *token, t_redir *redir, int redir_count, int i)
{
	redir[i].heredoc_fd = -1;
	redir[i].type = token->type;
	redir[i].redir_count = redir_count;
	token = token->next;
	redir[i].file_name = ft_strdup(token->value);
	if (!redir[i].file_name)
	{
		free_redir(redir, i);
		return (false);
	}
	redir[i].is_ambiguous = token->is_ambiguous;
	redir[i].state = token->state;
	return (true);
}

static t_redir	*create_redir(t_token *token)
{
	t_redir	*redir;
	int		redir_count;
	int		i;

	redir_count = redir_count_in_segment(token);
	redir = malloc(sizeof(t_redir) * redir_count);
	if (!redir)
		return (NULL);
	i = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type != WORD)
		{
			if (!set_redir(token, redir, redir_count, i))
				return (NULL);
			i++;
		}
		token = token->next;
	}
	return (redir);
}

static char	**set_args(t_token *token, int cmd_count)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (cmd_count + 1));
	if (!args)
		return (NULL);
	i = -1;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == WORD)
		{
			if (token->value[0] || token->empty_string)
			{
				args[++i] = ft_strdup(token->value);
				if (!args[i])
					return (free_all(args));
			}
		}
		else
			token = token->next;
		token = token->next;
	}
	args[++i] = NULL;
	return (args);
}

static bool	create_args(t_token *token, t_segment *segment)
{
	int			redir_count;
	int			cmd_count;

	redir_count = redir_count_in_segment(token);
	cmd_count = token_count_in_segment(token) - (redir_count * 2);
	segment->cmd_type = CMD_NOT_FOUND;
	segment->cmd_path = NULL;
	segment->args = NULL;
	if (cmd_count > 0)
	{
		segment->args = set_args(token, cmd_count);
		if (!segment->args)
			return (false);
	}
	return (true);
}

bool	create_segment(t_token *token, t_segment *segments, int segment_count)
{
	int	i;

	i = -1;
	while (++i < segment_count)
	{
		if (!create_args(token, &segments[i]))
			return (free_segment(segments, i));
		if (redir_count_in_segment(token) == 0)
			segments[i].redirections = NULL;
		else
		{
			segments[i].redirections = create_redir(token);
			if (!segments[i].redirections)
				return (free_segment(segments, i + 1));
		}
		segments[i].segment_count = segment_count;
		token = next_pipe(token);
	}
	return (true);
}
