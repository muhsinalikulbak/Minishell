/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:52:24 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/17 13:01:56 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	anlayse(char *cmd, t_token **token)
{
	int				len;
	t_token_type	token_type;
	
	len = ft_strlen(cmd);
	if (len == 1)
	{
		if (cmd[0] == '|')
		   token_type = TOKEN_PIPE;
		if (cmd[0] == '<')
		token_type = TOKEN_REDIR_IN;
		if (cmd[0] == '>')
		token_type = TOKEN_REDIR_OUT;
	}
	else if (len == 2)
	{
		if (cmd[0] == '<' && cmd[1] == '<')
		token_type = TOKEN_HEREDOC;
		if (cmd[0] == '>' && cmd[1] == '>')
		token_type = TOKEN_APPEND;
	}
	else
	token_type = TOKEN_WORD;
	insert_token(token, cmd, token_type);
}

static bool	scan(char *input_cmd, t_token **token)
{
	char	**scanned_cmd;
	int		i;

	i = 0;
	scanned_cmd = ft_split(input_cmd, ' ');
	if (!scanned_cmd)
	{
		perror("command could not scanned");
		return (false);
	}
	while (scanned_cmd[i])
	{
		anlayse(scanned_cmd[i], token);
		i++;
	}
	return (true);
}

t_token *lexer(char *command_line)
{
	t_token *token;
	
	token = NULL;
	scan(command_line, &token);
	return token;   
}