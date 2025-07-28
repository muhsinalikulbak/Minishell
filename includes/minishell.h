/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:39 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/26 19:01:52 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

/* Libft library */
# include "libft.h"

/* Project headers */
# include "builtins.h"
# include "env_manager.h"
# include "executor.h"
# include "lexer.h"
# include "parser.h"
# include "signals.h"
# include "utils.h"

extern volatile sig_atomic_t	g_signal_received;
#endif