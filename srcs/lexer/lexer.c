/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:52:24 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/26 18:11:04 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	init_state_data(t_lexer_data *data, t_token **token, char *input)
{
	data->token = token;
	data->token_value = NULL;
	data->input_line = input;
	data->input_length = ft_strlen(input);
	data->state = STATE_IDLE;
	data->prev_state = STATE_NORMAL;
	data->value_idx = 0;
	return (true);
}

static bool	split_line(char *input_line, t_lexer_data *data)
{
	int	i;

	i = -1;
	data->i = &i;
	while (input_line[++i])
	{
		if (data->state == STATE_IDLE)
		{
			if (!state_idle(data))
				return (false);
		}
		else if (data->state == STATE_IN_DQUOTE)
		{
			if (!state_double_quote(data, input_line[i]))
				return (false);
		}
		else if (data->state == STATE_IN_SQUOTE)
			state_single_quoute(data, input_line[i]);
		else if (data->state == STATE_NORMAL)
		{
			if (!state_normal(data, input_line[i]))
				return (false);
		}
	}
	return (last_state(data));
}

bool	lexer(t_token **token, char *input_line)
{
	t_lexer_data	data;
	bool			check_lexer;

	if (!init_state_data(&data, token, input_line))
		return (false);
	check_lexer = split_line(input_line, &data);
	if (!check_lexer)
		free_token(*token);
	return (check_lexer);
}
