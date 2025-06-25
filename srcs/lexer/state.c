/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 01:11:15 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/25 17:23:11 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_idle(t_lexer_data *data, char ch)
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
		check_operator(data);
}

void	state_normal(t_lexer_data *data, char ch)
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
		check_operator(data);
}

void	state_double_quote(t_lexer_data *data, char ch)
{
	data->prev_state = data->state;
	if (ch == '"')
		data->state = STATE_NORMAL;
	else
		data->token_value[data->value_idx++] = ch;
}

void	state_single_quoute(t_lexer_data *data, char ch)
{
	data->prev_state = data->state;
	if (ch == '\'')
		data->state = STATE_NORMAL;
	else
		data->token_value[data->value_idx++] = ch;
}

bool	last_state(t_lexer_data *data)
{
	data->token_value[data->value_idx] = '\0';
	if (data->state == STATE_NORMAL)
	{
		tokenize(data, data->token);
		return (true);
	}
	free(data->token_value);
	if (data->state == STATE_IN_DQUOTE)
		ft_putstr_fd("Quotation error, missing double quote (\")\n", 2);
	else
		ft_putstr_fd("Quotation error, missing single quote (\')\n", 2);
	return (false);
}
