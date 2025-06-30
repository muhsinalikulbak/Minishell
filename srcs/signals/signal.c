/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:03:40 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/01 00:08:42 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    ctrls(int sig)
{
    if (sig == SIGINT)
    {
        write(2, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void    handle_eof()
{
    exit(EXIT_FAILURE);
}

void signal_setup()
{
    struct sigaction sa_int;  // For SIGINT
    struct sigaction sa_quit; // For SIGQUIT
    
    // Set up SIGINT handler
    sa_int.sa_handler = &ctrls;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
    
    // Set up SIGQUIT to be ignored
    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}