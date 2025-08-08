/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:01:14 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/07 18:47:36 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*build_prompt_string(char *username, char *pwd)
{
	char	*temp1;
	char	*temp2;
	char	*prompt;

	temp1 = ft_strjoin("\001\033[1;32m\002", username);
	if (!temp1)
		return (NULL);
	temp2 = ft_strjoin(temp1, "\001\033[0m\002:\001\033[1;34m\002");
	free(temp1);
	if (!temp2)
		return (NULL);
	temp1 = ft_strjoin(temp2, pwd);
	free(temp2);
	if (!temp1)
		return (NULL);
	prompt = ft_strjoin(temp1, "\001\033[0m\002$ ");
	free(temp1);
	return (prompt);
}

static	char	*create_prompt(void)
{
	char	*pwd;
	char	*username;
	char	*prompt;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	username = getenv("USER");
	if (!username)
		return (free(pwd), NULL);
	prompt = build_prompt_string(username, pwd);
	free(pwd);
	if (!prompt)
		return (ft_strdup("$ "));
	return (prompt);
}

char	*get_input(bool is_heredoc)
{
	char				*line;
	char				*prompt;

	if (is_heredoc)
		line = readline("> ");
	else
	{
		prompt = create_prompt();
		if (!prompt)
		{
			line = readline("\001\033[1;32m\002Minishell$ \001\033[0m\002");
		}
		else
		{
			line = readline(prompt);
			free(prompt);
		}
	}
	return (line);
}
