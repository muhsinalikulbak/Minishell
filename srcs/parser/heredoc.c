/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:13:32 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/18 00:25:18 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_value_for_heredoc(char *line, int *i)
{
	char	*key;
	char	*value;
	int		j;

	j = ++(*i);
	if (ft_isdigit(line[j]))
		return ("");
	while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
		j++;
	key = ft_substr(line, *i, j - *i);
	if (!key)
		return (free(line), NULL);
	value = try_get_value(key);
	free(key);
	*i = j - 1;
	if (value == NULL)
		return ("");
	return (value);
}

static bool heredoc_expand(char *line, int pipefd[])
{
	char	*value;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && check_no_expand_for_heredoc(line, i))
		{
			value = get_value_for_heredoc(line, &i);
			if (!value)
				return (free(line), false);
			write(pipefd[1], value, ft_strlen(value));
		}
		else
			write(pipefd[1], &line[i], 1);
		i++;
	}
	return (true);
}

static bool	heredoc(char *delimiter, int *fd, bool is_it_expandable)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (false);
	line = get_input(true);
	if (!line)
		return (close_pipefd(pipefd));
	while (!str_equal(delimiter, line))
	{
		if (is_it_expandable && ft_strchr(line, '$'))
		{
			if (!heredoc_expand(line, pipefd))
				return (close_pipefd(pipefd));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		else
			write_pipefd(line, pipefd);
		line = get_input(true);
		if (!line)
			return (close_pipefd(pipefd));
	}
	return (heredoc_finishing(line, pipefd, fd));
}

static bool	heredoc_scan(t_redir *redir)
{
	int		i;
	bool	is_it_expandable;

	i = 0;
	while (i < redir->redir_count)
	{
		if (redir[i].type == TOKEN_HEREDOC)
		{
			is_it_expandable = redir[i].state == STATE_NORMAL;
			if (!heredoc(redir[i].filename, &redir[i].heredoc_fd, is_it_expandable))
				return (false);
		}
		i++;
	}
	return (true);
}

bool    heredoc_init(t_segment *segments)
{
	int		i;
	t_redir	*redir;

	i = 0;
	while (i < segments->segment_count)
	{
		redir = segments[i].redirections;
		if (redir)
		{
			if (!heredoc_scan(redir))
				return (false);
		}
		i++;
	}
	return (true);
}







// EN SON KALDIRILACAK

static void print_heredoc_content(int fd, int segment_idx, int heredoc_idx)
{
    char    buffer[1024];
    ssize_t bytes_read;
    int     original_pos;
    int     i, line_start;
    
    (void)segment_idx; // Unused parameter
    
    if (fd == -1)
    {
        printf("    📄 Heredoc %d: No data (fd: -1)\n", heredoc_idx);
        return;
    }
    
    // Mevcut pozisyonu kaydet
    original_pos = lseek(fd, 0, SEEK_CUR);
    
    // Başa git
    lseek(fd, 0, SEEK_SET);
    
    printf("    📄 Heredoc %d (fd: %d):\n", heredoc_idx, fd);
    printf("    ┌─────────────────────────────────────────────┐\n");
    
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        
        // Manuel parsing - boş satırları da göster
        line_start = 0;
        i = 0;
        while (i < bytes_read)  // 🔥 Değişiklik: i <= bytes_read yerine i < bytes_read
        {
            if (buffer[i] == '\n')
            {
                // Satırı null-terminate et
                buffer[i] = '\0';
                    
                // Boş satır bile olsa yazdır
                printf("    │ %s\n", &buffer[line_start]);
                
                line_start = i + 1;
            }
            i++;
        }
        
        // 🔥 Yeni: Eğer son karakter \n değilse, kalan kısmı yazdır
        if (line_start < bytes_read)
        {
            printf("    │ %s\n", &buffer[line_start]);
        }
    }
    
    printf("    └─────────────────────────────────────────────┘\n");
    
    // Orijinal pozisyona geri dön
    lseek(fd, original_pos, SEEK_SET);
}

void print_heredoc_data(t_segment *segments)
{
    int     i, j;
    t_redir *redir;
    int     heredoc_count;
    
    if (!segments)
    {
        printf("❌ No segments to display heredoc data\n");
        return;
    }
    
    printf("\n🔍 HEREDOC DATA INSPECTION:\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    i = 0;
    while (i < segments->segment_count)
    {
        printf("\n📂 SEGMENT %d:\n", i);
        printf("───────────────────────────────────────────────────────\n");
        
        redir = segments[i].redirections;
        if (!redir)
        {
            printf("  ⚠️  No redirections in this segment\n");
            i++;
            continue;
        }
        
        heredoc_count = 0;
        j = 0;
        while (j < redir->redir_count)
        {
            if (redir[j].type == TOKEN_HEREDOC)
            {
                printf("  🔸 Heredoc found: delimiter='%s'\n", redir[j].filename);
                print_heredoc_content(redir[j].heredoc_fd, i, heredoc_count);
                heredoc_count++;
            }
            j++;
        }
        
        if (heredoc_count == 0)
            printf("  ℹ️  No heredocs in this segment\n");
        else
            printf("  ✅ Total heredocs in segment %d: %d\n", i, heredoc_count);
            
        i++;
    }
    
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("🏁 Heredoc inspection completed!\n\n");
}
