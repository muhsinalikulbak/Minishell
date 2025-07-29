/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:44:02 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/30 02:37:20 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	start_heredoc(char *delimiter, int *fd, bool is_it_expandable)
{
	int		pipefd[2];
	pid_t	child_pid;

	if (pipe(pipefd) == -1)
		return (false);
	heredoc_parent_signal_setup();
	child_pid = fork();
	if (child_pid == -1)
		return (close_pipefd(pipefd));
	if (child_pid == 0)
	{
		heredoc_child_process(delimiter, pipefd, is_it_expandable);
		exit(EXIT_FAILURE);
	}
	else
		return (heredoc_parent_process(pipefd, child_pid, fd));
}

static bool	heredoc_scan(t_redir *redir)
{
	bool	is_it_expandable;
	char	*delimiter;
	int		i;

	i = 0;
	while (i < redir->redir_count)
	{
		if (redir[i].type == HEREDOC)
		{
			delimiter = redir[i].file_name;
			is_it_expandable = redir[i].state == STATE_NORMAL;
			if (!start_heredoc(delimiter, &redir[i].heredoc_fd, is_it_expandable))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	heredoc_init(t_segment *segments)
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

/*
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
		while (i < bytes_read)  
		// 🔥 Değişiklik: i <= bytes_read yerine i < bytes_read
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
		printf("❌ No segments to display start_heredoc data\n");
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
			if (redir[j].type == HEREDOC)
			{
				printf("  🔸 Heredoc found: delimiter='%s'\n", redir[j].file_name);
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
*/