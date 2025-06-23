/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:01:14 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/23 13:20:58 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_input(bool quote_state)
{
	char *line;

	if (quote_state)
		line = readline("minishell~$ ");
	else
		line = readline("> ");
	if (!line)
		return (NULL);
	return (line);
}
