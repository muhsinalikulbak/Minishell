/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:52:24 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/22 15:13:57 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	state_data_init(t_state_data *data, t_token **token, char *input)
{
	data->token = token;
	data->token_value = NULL;
	data->input_line = input;
	data->input_length = ft_strlen(input);
	data->state = STATE_IDLE;
	data->prev_state = STATE_NORMAL;
	data->value_idx = 0;
	data->history = ft_strdup(input); // Double free'den kaçınmak için
}

void	tokenize(t_state_data *data, t_token **token)
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

static bool	split_line(char *input_line, t_state_data *data)
{
	int	i;

	i = 0;
	while (input_line[i])
	{
		if (data->state == STATE_IDLE && input_line[i] != ' ')
			state_idle(data, input_line[i]);
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

char	*lexer(t_token **token, char *input_line)
{
	t_state_data	data;
	bool			quote_state;
	char			*temp;

	state_data_init(&data, token, input_line); 		// Lexer başladı
	quote_state = split_line(input_line, &data); 	// Ayrıştırma yapıldı tokenlar oluşturuldu.
	while (!quote_state) 			// Komut geçersiz "  quote ile biterse veri alınmaya devam eder
	{
		free(data.input_line); // eski input'u freele
		input_line = get_input(false); 	// yeni inputu al (readline ile)
		data.token_value[data.value_idx++] = '\n'; // new_line eklenir
		data.token_value[data.value_idx] = '\0'; // null terminate edilir
		temp = data.token_value; 		// sonraki input eklendikten sonra free yapılacak
		data.input_length += ft_strlen(input_line);
		data.token_value = malloc(data.input_length + 2);
		ft_memmove(data.token_value, temp, ft_strlen(temp));
		free(temp); // eski token_value'yu freele
		temp = data.history;
		data.history = ft_strjoin(data.history, "\n");
		free(temp); // eski history'i freele
		temp = data.history;
		data.history = ft_strjoin(data.history, input_line);
		free(temp); // eski history'i freele
		data.input_line = input_line;
		quote_state = split_line(input_line, &data);
	}
	free(data.input_line);
	return (data.history);
}
