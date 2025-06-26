/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:52:24 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/26 15:56:24 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	state_data_init(t_lexer_data *data, t_token **token, char *input)
{
	data->token = token;
	data->token_value = NULL;
	data->input_line = input;
	data->input_length = ft_strlen(input);
	data->state = STATE_IDLE;
	data->prev_state = STATE_NORMAL;
	data->value_idx = 0;
}

void	tokenize(t_lexer_data *data, t_token **token)
{
	int				len;
	t_token_type	token_type;
	t_token_state	prev_state;

	len = ft_strlen(data->token_value);
	prev_state = data->prev_state;
	if (prev_state == STATE_IN_DQUOTE || prev_state == STATE_IN_SQUOTE)
	{
		insert_token(token, TOKEN_WORD, data->token_value);
		return ;
	}
	else if (ft_strncmp(data->token_value, "|", len) && len == 1)
		token_type = TOKEN_PIPE;
	else if (ft_strncmp(data->token_value, "<", len) && len == 1)
		token_type = TOKEN_REDIR_IN;
	else if (ft_strncmp(data->token_value, ">", len) && len == 1)
		token_type = TOKEN_REDIR_OUT;
	else if (ft_strncmp(data->token_value, "<<", len) && len == 2)
		token_type = TOKEN_HEREDOC;
	else if (ft_strncmp(data->token_value, ">>", len) && len == 2)
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
			state_idle(data);
		else if (data->state == STATE_IN_DQUOTE)
			state_double_quote(data, input_line[i]);
		else if (data->state == STATE_IN_SQUOTE)
			state_single_quoute(data, input_line[i]);
		else if (data->state == STATE_NORMAL)
			state_normal(data, input_line[i]);
		i++;
	}
	return (last_state(data));
}

bool	lexer(t_token **token, char *input_line)
{
	t_lexer_data	data;
	bool			check_lexer;

	state_data_init(&data, token, input_line);
	check_lexer = split_line(input_line, &data);
	if (!check_lexer)
		free_token(token);
	return (check_lexer);
}
