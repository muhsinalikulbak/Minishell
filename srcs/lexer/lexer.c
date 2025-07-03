/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:52:24 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/03 03:00:56 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	state_data_init(t_lexer_data *data, t_token **token, char *input)
{
	data->token = token;
	data->token_value = NULL;
	data->input_line = input;
	data->input_length = ft_strlen(input);
	data->state = STATE_IDLE;
	data->prev_state = STATE_NORMAL;
	data->value_idx = 0;
	data->inv_map = malloc(sizeof(int) * 256);
	if (!data->inv_map)
		return (false);
	init_inv_map(data->inv_map);
	return (true);
}

void	tokenize(t_lexer_data *data, t_token **token)
{
	t_token_type	token_type;
	t_token_state	prev_state;

	prev_state = data->prev_state;
	if (prev_state == STATE_IN_DQUOTE || prev_state == STATE_IN_SQUOTE)
	{
		insert_token(token, TOKEN_WORD, data->token_value);
		return ;
	}
	else if (str_equal(data->token_value, "|"))
		token_type = TOKEN_PIPE;
	else if (str_equal(data->token_value, "<"))
		token_type = TOKEN_REDIR_IN;
	else if (str_equal(data->token_value, ">"))
		token_type = TOKEN_REDIR_OUT;
	else if (str_equal(data->token_value, "<<"))
		token_type = TOKEN_HEREDOC;
	else if (str_equal(data->token_value, ">>"))
		token_type = TOKEN_APPEND;
	else
		token_type = TOKEN_WORD;
	insert_token(token, token_type, data->token_value);
}

static bool	split_line(char *input_line, t_lexer_data *data)
{
	int	i;

	i = 0;
	data->i = &i;
	while (input_line[i])
	{
		if (data->state == STATE_IDLE)
		{
			if (!state_idle(data))
				return (false);
		}
		else if (data->state == STATE_IN_DQUOTE)
			state_double_quote(data, input_line[i]);
		else if (data->state == STATE_IN_SQUOTE)
			state_single_quoute(data, input_line[i]);
		else if (data->state == STATE_NORMAL)
		{
			if (!state_normal(data, input_line[i]))
				return (false);
		}
		i++;
	}
	return (last_state(data));
}

bool	lexer(t_token **token, char *input_line)
{
	t_lexer_data	data;
	bool			check_lexer;

	if (!state_data_init(&data, token, input_line))
		return (false);
	check_lexer = split_line(input_line, &data);
	if (!check_lexer)
		free_token(token);
	free(data.inv_map);
	return (check_lexer);
}
