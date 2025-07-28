/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:34 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/26 13:57:35 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

bool	str_equal(char *str1, char *str2);
int		get_exit_code(void);
void	set_exit_code(int status);
bool	close_pipefd(int pipefd[2]);

#endif