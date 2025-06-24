/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:43:49 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/25 02:03:41 by muhsin           ###   ########.fr       */
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

// static bool	check_redir(t_lexer_data *data, char ch)
// {
// 	// kontrol yapılıcak
// }

static bool	tokenize_pipe(t_lexer_data *data)
{
	data->token_value[data->value_idx] = '\0';
	tokenize(data, data->token);
	data->token_value = ft_strdup("|");
	tokenize(data, data->token);
	data->token_value = NULL;
	data->prev_state = data->state;
	data->state = STATE_IDLE;
	(*data->i)--;
	return (true);
}

bool	check_operator(t_lexer_data *data)
{
	char	ch;
	
	ch = data->input_line[(*data->i)++];
	while (ch != '\0')
	{
		if (ch == '\'' || ch == '\"')
			return (set_quote(data, ch));
		else if (ch == '|')
			return (tokenize_pipe(data));
		else if (ch == ' ')
		{
			data->token_value[data->value_idx] = '\0';
			tokenize(data, data->token);
			data->token_value = NULL;
			data->prev_state = data->state;
			data->state = STATE_IDLE;
			(*data->i)--;
			return (true);
		}
		// else if (ch != '<' && ch != '>')
		// {
		// 	check_redir(data, ch);	
		// }
		else
			data->token_value[data->value_idx++] = ch;
		ch = data->input_line[(*data->i)++];
	}
	return (true);
	
}
