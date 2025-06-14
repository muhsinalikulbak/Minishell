/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:56:52 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/13 18:05:26 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char *get_input(){
    
    char *line = readline("minishell>");

    if (!line)
        return NULL;

    if (*line)
        add_history(line);
    
    return line;
}