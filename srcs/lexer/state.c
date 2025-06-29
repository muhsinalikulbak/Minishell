/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 01:11:15 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/30 00:47:02 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	state_idle(t_lexer_data *data)
{
	int		len;

	len = data->input_length;
	data->state = STATE_NORMAL;
	if (data->token_value == NULL)
	{
		data->token_value = (char *)ft_calloc(len + 2, sizeof(char));
		if (data->token_value == NULL)
			return (false);
		data->value_idx = 0;
	}
	past_space(data);
	(*data->i)--;
	return (true);
}

bool	state_normal(t_lexer_data *data, char ch)
{
	if (ch == ' ' || (ch >= 9 && ch <= 13))
	{
		data->token_value[data->value_idx] = '\0';
		tokenize(data, data->token); //bool değeri kontrol 
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
	else if (!check_operator(data))
		return (false);
	return (true);
}

void	state_double_quote(t_lexer_data *data, char ch)
{
	if (ch == '"')
	{
		data->prev_state = data->state;
		data->state = STATE_NORMAL;
	}
	else
		data->token_value[data->value_idx++] = ch;
}

void	state_single_quoute(t_lexer_data *data, char ch)
{
	if (ch == '\'')
	{
		data->prev_state = data->state;
		data->state = STATE_NORMAL;
	}
	else
		data->token_value[data->value_idx++] = ch;
}

bool	last_state(t_lexer_data *data)
{
	if (data->token_value != NULL)
	{
		data->token_value[data->value_idx] = '\0';
		if (data->state == STATE_NORMAL)
		{
			tokenize(data, data->token);
			return (true);
		}
		else
		{
			free(data->token_value);
			if (data->state == STATE_IN_DQUOTE)
				ft_putendl_fd("Quotation error, missing double quote (\")", 2);
			else
				ft_putendl_fd("Quotation error, missing single quote (\')", 2);
			return (false);
		}
	}
	if (get_token_count(*data->token) == 0)
		return (false);
	return (true);
}
