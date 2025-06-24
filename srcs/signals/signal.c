/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 09:03:40 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/24 09:13:43 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctr_c(int sig)
{
	write(1,"hello world from signal\n",25);
}

void    ctrl_d(int sig){}

void signal_setup(){

    struct sigaction	sa;

	sa.sa_handler = &ctr_c;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}