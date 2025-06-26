/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:43:49 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/26 14:19:19 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	set_quote(t_lexer_data *data, char ch)
{
	data->prev_state = data->state;
	if (ch == '\'')
		data->state = STATE_IN_SQUOTE;
	else
		data->state = STATE_IN_DQUOTE;
	return (true);
}

static bool	check_redir(t_lexer_data *data)
{
	return (true);
}

static bool	tokenize_pipe(t_lexer_data *data)
{
	int	len;

	data->token_value[data->value_idx] = '\0';
	len = ft_strlen(data->token_value);
	if (len == 0)
		free(data->token_value);
	else
		tokenize(data, data->token);
	data->token_value = ft_strdup("|");
	data->prev_state = data->state;
	data->state = STATE_IDLE;
	tokenize(data, data->token);
	data->token_value = NULL;
	return (true);
}

bool	check_operator(t_lexer_data *data)
{
	char	ch;

	ch = data->input_line[(*data->i)];
	while (ch != '\0')
	{
		if (ch == '\'' || ch == '\"')
			return (set_quote(data, ch));
		else if (ch == '|')
			return (tokenize_pipe(data));
		else if (ch == ' ')
		{
			state_normal(data, ch);
			return (true);
		}
		else if (ch == '<' || ch == '>')
			return (check_redir(data));
		else
			data->token_value[data->value_idx++] = ch;
		ch = data->input_line[++(*data->i)];
	}
	(*data->i)--;
	return (true);
}
