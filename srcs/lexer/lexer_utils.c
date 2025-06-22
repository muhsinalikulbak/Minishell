/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 01:11:15 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/22 14:10:11 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_idle(t_state_data *data, char ch)
{
	int	len;

	len = data->input_length;
	data->state = STATE_NORMAL;
	if (data->token_value == NULL)
	{
		data->token_value = (char *)ft_calloc(len + 2, sizeof(char));
		data->value_idx = 0;
	}
	if (ch == '"')
		data->state = STATE_IN_DQUOTE;
	else if (ch == '\'')
		data->state = STATE_IN_SQUOTE;
	else
		data->token_value[data->value_idx++] = ch;
}

void	state_normal(t_state_data *data, char ch)
{
	if (ch == ' ')
	{
		data->token_value[data->value_idx] = '\0';
		tokenize(data, data->token);
		data->token_value = NULL;
		data->prev_state = STATE_NORMAL;
		data->state = STATE_IDLE;
	}
	else if (ch == '"')
	{
		data->prev_state = data->state;
		data->state = STATE_IN_DQUOTE;
	}
	else if (ch == '\'')
	{
		data->prev_state = data->state;
		data->state = STATE_IN_SQUOTE;
	}
	else
		data->token_value[data->value_idx++] = ch;
}

void	state_double_quote(t_state_data *data, char ch)
{
	data->prev_state = data->state;
	if (ch == '"')
		data->state = STATE_NORMAL;
	else
		data->token_value[data->value_idx++] = ch;
}

void	state_single_quoute(t_state_data *data, char ch)
{
	data->prev_state = data->state;
	if (ch == '\'')
		data->state = STATE_NORMAL;
	else
		data->token_value[data->value_idx++] = ch;
}

bool	last_state(t_state_data *data)
{
	if (data->token_value != NULL)
	{
		if (data->state == STATE_NORMAL)
		{
			data->token_value[data->value_idx] = '\0';
			tokenize(data, data->token);
			return (true);
		}
		else
			return (false);
	}
}
