/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 03:29:12 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/13 03:39:38 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool set_redir(t_token *token)
{
	
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
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		if (token->type >= 2 && token->type <= 5)
		{
			redir[i].heredoc_fd = -1;
			redir[i].type = token->type;
			redir[i].redir_count = redir_count;
			token = token->next;
			redir[i].filename = ft_strdup(token->value);
			if (!redir[i].filename)
			{
				free_redir(redir, i);
				return (NULL);
			}
			redir[i].state = token->state;
			i++;
		}
		token = token->next;
	}
	return (redir);
}

static char **set_args(t_token *token, int cmd_count)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (cmd_count + 1));
	if (!args)
		return (NULL);
	i = -1;
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
		{
			args[++i] = ft_strdup(token->value);
			if (!args[i])
			{
				free_all(args);
				return (NULL);
			}
		}
		else if (token->type >= 2 && token->type <= 5)
			token = token->next;
		token = token->next;
	}
	args[i] = NULL;
	return (args);
}

static bool	create_args(t_token *token, t_segment segment)
{
	int			redir_count;
	int			cmd_count;

	redir_count = redir_count_in_segment(token);
	cmd_count = token_count_in_segment(token) - (redir_count * 2);
	if (cmd_count > 0)
	{
		segment.args = set_args(token, cmd_count);
		if (!segment.args)
			return (false);
	}
	else
		segment.args = NULL;
	return (true);
}

bool    create_segment(t_token *token, t_segment *segments, int segment_count)
{
	int	i;

	i = -1;
	while (++i < segment_count)
	{
		if (!create_args(token, segments[i]))
		{
			free_segment(segments, i);
			return (false);
		}
		if (redir_count_in_segment(token) == 0)
			segments[i].redirections = NULL;
		else
		{
			segments[i].redirections = create_redir(token);
			if (!segments[i].redirections)
			{
				free_segment(segments, i + 1);
				return (false);
			}
		}
		segments[i].segment_count = segment_count;
		token = next_pipe(token);
	}
	return (true);
}
