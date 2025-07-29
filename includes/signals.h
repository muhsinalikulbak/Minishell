/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:32 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/29 18:50:55 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void		signal_setup(void);
void		child_signal_setup(void);
void		handle_eof(void);
extern void	rl_replace_line(const char *text, int clear_undo);

#endif