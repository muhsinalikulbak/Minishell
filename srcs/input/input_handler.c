/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:56:52 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/24 17:46:34 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_input(){
	
	char *line = readline("minishell>");
	if (!line)
		handle_eof();

	if (*line)
		add_history(line);
	
	return line;
}