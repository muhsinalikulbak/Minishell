/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:01:14 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/26 18:10:45 by omakbas          ###   ########.fr       */
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

char	*get_input(bool is_heredoc)
{
	char	*line;
	// Leak bakmak için burayı aç readlien'ı kapat ve maindeki sonsuz while loop'u kaldır
	// write(1, "minishell~$ ", 12);
	// line = get_next_line(STDIN_FILENO);
	if (is_heredoc)
		line = readline("> ");
	else
		line = readline("minishell~$ ");
	return (line);
}
