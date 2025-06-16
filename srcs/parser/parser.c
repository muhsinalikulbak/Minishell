/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:52:32 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/17 01:29:59 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(t_token *token_list)
{
	t_cmd	*commands;

	if (!syntax_check(token_list))
		return (NULL);
	
	return (commands);
}
