/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:56:52 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/20 00:17:15 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_input(){
	
	char *line = readline("minishell~$");

	if (!line && !*line)
		return NULL;

	if (*line)
		add_history(line);
	
	return line;
}