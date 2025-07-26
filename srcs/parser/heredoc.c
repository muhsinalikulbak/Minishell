/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:13:32 by muhsin            #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/07/26 20:52:38 by omakbas          ###   ########.fr       */
=======
/*   Updated: 2025/07/26 19:32:01 by mkulbak          ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void heredoc_child_signal_setup(void)
{
    struct sigaction sa;
    sa.sa_handler = SIG_DFL; // Default: terminate on SIGINT/SIGQUIT
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

static void	heredoc_parent_signal_setup(void)
{
	struct sigaction sa;
	
	// Ignore SIGINT/SIGQUIT in parent during heredoc collection
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	heredoc_restore_signals(void)
{
	// Restore original signal handlers after heredoc
	// This should call your main signal_setup() function
	signal_setup();
}

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

static bool	heredoc_expand(char *line, int pipefd[])
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

static bool	heredoc_child_process(char *delimiter, int pipefd[2], bool is_it_expandable)
{
	char	*line;

	// Setup signal handlers for child process
	heredoc_child_signal_setup();
	
	// Close read end in child
	close(pipefd[0]);

	line = get_input(true);
    
	if (!line)
	{
        ft_putstr_fd("bash: warning: here-document delimited by end-of-file (wanted `", 2);
        ft_putstr_fd(delimiter, 2);
        ft_putendl_fd("')", 2);
        close(pipefd[1]);
        exit(0);
	}

	while (!str_equal(delimiter, line))
	{
		if (is_it_expandable && ft_strchr(line, '$'))
		{
			if (!heredoc_expand(line, pipefd))
			{
				close(pipefd[1]);
				exit(1);
			}
			write(pipefd[1], "\n", 1);
			free(line);
		}
		else
			write_pipefd(line, pipefd);
		
		line = get_input(true);
		if (!line)
		{
			close(pipefd[1]);
			exit(0); // EOF (Ctrl-D)
		}
	}
	
	free(line);
	close(pipefd[1]);
	exit(0);
}

static bool	heredoc(char *delimiter, int *fd, bool is_it_expandable)
{
	int		pipefd[2];
	pid_t	child_pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (false);

	// Setup parent signal handling (ignore signals during heredoc)
	heredoc_parent_signal_setup();

	child_pid = fork();
	if (child_pid == -1)
		return (close_pipefd(pipefd));

	if (child_pid == 0)
	{
		// Child process - collect heredoc input
		heredoc_child_process(delimiter, pipefd, is_it_expandable);
		// Should never reach here
		exit(1);
	}
	else
	{
		// Parent process - wait for child
		close(pipefd[1]); // Close write end in parent
		
		// Wait for child to complete
		waitpid(child_pid, &status, 0);
		
		// Restore original signal handlers
		heredoc_restore_signals();
		
		// Check if child was killed by signal
		if (WIFSIGNALED(status))
		{
			// Child was interrupted (Ctrl-C, etc.)
			close(pipefd[0]);
			*fd = -1;
			return (true);
		}
		
		// Check if child exited with error
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			close(pipefd[0]);
			*fd = -1;
			return (false);
		}
		
		// Success - return read end of pipe
		*fd = pipefd[0];
		return (true);
	}
}

static bool	heredoc_scan(t_redir *redir)
{
	bool	is_it_expandable;
	char	*delimiter;
	int		i;

	i = 0;
	while (i < redir->redir_count)
	{
		if (redir[i].type == TOKEN_HEREDOC)
		{
			delimiter = redir[i].filename;
			is_it_expandable = redir[i].state == STATE_NORMAL;
			if (!heredoc(delimiter, &redir[i].heredoc_fd, is_it_expandable))
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
