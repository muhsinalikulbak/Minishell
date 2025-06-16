/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:56:52 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/16 03:04:22 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *get_input(){
    
    char *line = readline("minishell>");

    if (!line)
        return NULL;

    if (*line)
        add_history(line);
    
    return line;
}