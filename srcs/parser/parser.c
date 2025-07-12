/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:52:32 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/12 22:08:17 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*next_pipe(t_token *token)
{
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		token = token->next;
	}
	return (token);
}

t_redir	*create_redir(t_token *token)
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
				// i  'e kadar free'le 
				return (NULL);
			}
			redir[i].state = token->state;
			i++;
		}
		token = token->next;
	}
}

static bool	create_segment(t_token *token, t_segment segment)
{
	char		**args;
	int			redir_count;
	int			cmd_count;
	int			k;

	k = 0;
	args = NULL;
	redir_count = redir_count_in_segment(token);
	cmd_count = token_count_in_segment(token) - (redir_count * 2);
	if (cmd_count > 0)
	{
		args = malloc(sizeof(char *) * (cmd_count + 1));
		if (!args)
			return (false);
		while (token != NULL && token->type != TOKEN_PIPE)
		{
			if (token->type == TOKEN_WORD)
			{
				args[k] = ft_strdup(token->value);
				if (!args[k])
				{
					free_all(args);
					return (false);
				}
				k++;
			}
			else if (token->type >= 2 && token->type <= 5)
				token = token->next;
			token = token->next;
		}
		args[k] = NULL;
	}
	segment.args = args;
	return (true);
}

t_segment	*parser(t_token *token)
{
	t_segment	*segments;
	int			segment_count;
	int			i;

	if (!syntax_check(token))
		return (NULL);
	segment_count = get_segment_count(token);
	segments = malloc(sizeof(t_segment) * segment_count);
	if (!segments)
		return (NULL);
	i = 0;
	while (i < segment_count)
	{
		if (!create_segment(token, segments[i]))
		{
			// i ' e kadar free yap sonra segments'i free'le
			// B
		}
		if (redir_count_in_segment(token) == 0)
			segments[i].redirections = NULL;
		else
		{
			segments[i].redirections = create_redir(token);
			if (!segments[i].redirections)
			{
					// segment free return NULL
			}
		}
		segments[i].segment_count = segment_count;
		i++;
	}
	return (NULL);
}
