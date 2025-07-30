/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:01:14 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/29 18:15:10 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define BUFFER_SIZE 4
/* 
işin bitince tekrar yoruma al
static char	*ft_next(char	*buf)
{
	int		i;
	int		j;
	char	*new_buf;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	new_buf = malloc((ft_strlen(buf) - i + 1) * sizeof(char));
	if (!new_buf)
		return (NULL);
	j = 0;
	while (buf[i])
		new_buf[j++] = buf[i++];
	new_buf[j] = '\0';
	free(buf);
	return (new_buf);
}

static char	*ft_line(char *buf)
{
	char	*line;
	int		i;

	i = 0;
	if (!buf)
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	line = ft_substr(buf, 0, i);
	return (line);
}

static char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

static char	*read_file(int fd, char *res)
{
	int		byte_read;
	char	*buf;

	if (!res)
		res = ft_strdup("");
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(res);
			free(buf);
			return (NULL);
		}
		buf[byte_read] = '\0';
		res = ft_free(res, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (res);
}

static char	*get_next_line(int fd)
{
	static char		*buf;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = read_file(fd, buf);
	if (!buf)
	{
		return (NULL);
	}
	line = ft_line(buf);
	buf = ft_next(buf);
	if (!*line)
	{
		if (!*line)
			free(line);
		return (NULL);
	}
	return (line);
}*/

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
			ft_putendl_fd("minishell: prompt creation failed", 2);
			prompt = ft_strdup("$ ");
		}
		line = readline(prompt);
		free(prompt);
	}
	return (line);
}
