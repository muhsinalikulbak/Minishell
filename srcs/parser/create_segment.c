/* ************************************************************************** */
/*                                                                            */
/*                      {
                printf("    \033[1;34m[%d]\033[0m ", j + 1);
                printf("\033[1;37mType\033[0m: \033[1;33m%s\033[0m, ", 
                       redir_type[segments[i].redirections[j].type]);
                printf("\033[1;37mFile\033[0m: \033[1;33m\"%s\"\033[0m, ", 
                       segments[i].redirections[j].filename);
                printf("\033[1;37mState\033[0m: \033[1;33m%s\033[0m", 
                       token_state[segments[i].redirections[j].state]);
                if (segments[i].redirections[j].type == TOKEN_HEREDOC)
                    printf(", \033[1;37mHeredoc_fd\033[0m: \033[1;33m%d\033[0m", 
                           segments[i].redirections[j].heredoc_fd);                                   :::      ::::::::   */
/*   create_segment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 03:29:12 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/27 03:10:44 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	set_redir(t_token *token, t_redir *redir, int redir_count, int i)
{
	redir[i].heredoc_fd = -1;
	redir[i].type = token->type;
	redir[i].redir_count = redir_count;
	token = token->next;
	redir[i].filename = ft_strdup(token->value);
	if (!redir[i].filename)
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
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		if (token->type != TOKEN_WORD) // PIPE VE WORD DEĞİLSE REDİRECTİONDUR
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
	while (token != NULL && token->type != TOKEN_PIPE)
	{
		if (token->type == TOKEN_WORD)
		{
			args[++i] = ft_strdup(token->value);
			if (!args[i])
				return (free_all(args));
		}
		else // PIPE VE TOKEN_WORD DEĞİLSE REDİRECTİONDUR
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









// Bu en son silinecek - test için
void print_segment_list(t_segment *segments, int segment_count)
{
    if (!segments)
    {
        printf("\033[1;31m[Error] Empty segment list\033[0m\n");
        return;
    }

    char *redir_type[] = {
        "TOKEN_WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "APPEND", "HEREDOC", NULL
    };
    
    char *token_state[] = {
        "NORMAL", "IN_DQUOTE", "IN_SQUOTE", "IDLE", NULL
    };

    printf("\033[1;32m=== SEGMENT LIST ===\033[0m\n");
    
    for (int i = 0; i < segment_count; i++)
    {
        printf("\033[1;35m[Segment %d]\033[0m\n", i + 1);
        
        // Args yazdır
        if (segments[i].args)
        {
            printf("  \033[1;36mArgs\033[0m: ");
            for (int j = 0; segments[i].args[j]; j++)
            {
                if (j > 0) printf(" ");
                printf("\033[1;33m\"%s\"\033[0m", segments[i].args[j]);
            }
            printf("\n");
        }
        else
        {
            printf("  \033[1;36mArgs\033[0m: \033[1;31mNULL\033[0m\n");
        }
        
        // Redirections yazdır
        if (segments[i].redirections)
        {
            printf("  \033[1;36mRedirections\033[0m:\n");
            for (int j = 0; j < segments[i].redirections[0].redir_count; j++)
            {
                printf("    \033[1;34m[%d]\033[0m ", j + 1);
                printf("\033[1;37mType\033[0m: \033[1;33m%s\033[0m, ", 
                       redir_type[segments[i].redirections[j].type]);
                printf("\033[1;37mFile\033[0m: \033[1;33m\"%s\"\033[0m, ", 
                       segments[i].redirections[j].filename);
                printf("\033[1;37mState\033[0m: \033[1;33m%s\033[0m", 
                       token_state[segments[i].redirections[j].state]);
                if (segments[i].redirections[j].type == TOKEN_HEREDOC)
                    printf(", \033[1;37mHeredoc_fd\033[0m: \033[1;33m%d\033[0m", 
                           segments[i].redirections[j].heredoc_fd);
                printf("\n");
            }
        }
        else
        {
            printf("  \033[1;36mRedirections\033[0m: \033[1;31mNULL\033[0m\n");
        }
        
        if (i < segment_count - 1)
            printf("  \033[1;32m↓ PIPE ↓\033[0m\n");
        printf("\n");
    }
    
    printf("\033[1;32m=== End of Segment List ===\033[0m\n");
}
