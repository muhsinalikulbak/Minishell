/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:43:49 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/04 10:44:47 by muhsin           ###   ########.fr       */
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

bool	tokenize_prev_value(t_lexer_data *data)
{
	int		len;
	int		idx;
	char	*line;

	data->token_value[data->value_idx] = '\0';
	len = ft_strlen(data->token_value);
	idx = *data->i;
	line = data->input_line;
	if (idx - 2 >= 0)
	{
		if ((line[idx - 1] == '"' && line[idx - 2] == '"')
			|| (line[idx - 1 == '\''] && line[idx - 2] == '\''))
		{
			data->empty_string = true;
			if (!tokenizer(data))
				return (false);
			return (true);
		}
	}
	if (len == 0 && !data->expanding) // Burası eğer expand edilmeden boş bir string ise free edilmeli, boş stringler çıkarılıyor.
		free(data->token_value);
	else if (!tokenizer(data))
		return (false);
	return (true);
}

static bool	tokenize_operator(t_lexer_data *data, char *operator)
{
	if (!tokenize_prev_value(data))
		return (false);
	data->token_value = ft_strdup(operator);
	if (data->token_value == NULL)
	{
		ft_putendl_fd("memory allocation failed", 2);
		return (false);
	}
	data->prev_state = STATE_NORMAL;
	data->state = STATE_IDLE;
	if (!tokenizer(data))
		return (false);
	data->token_value = NULL;
	return (true);
}

static bool	check_redir(t_lexer_data *data)
{
	int		i;
	char	*line;

	line = data->input_line;
	i = *data->i;
	if (line[i] == '>' && line[i + 1] != '>' && line[i + 1] != '<')
		return (tokenize_operator(data, ">"));
	if (line[i] == '<' && line[i + 1] != '<' && line[i + 1] != '>')
		return (tokenize_operator(data, "<"));
	if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] != '>'
		&& line[i + 2] != '<')
	{
		(*data->i)++;
		return (tokenize_operator(data, ">>"));
	}
	if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] != '<'
		&& line[i + 2] != '>')
	{
		(*data->i)++;
		return (tokenize_operator(data, "<<"));
	}
	print_redir_error(line, i);
	free(data->token_value);
	return (false);
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
			return (tokenize_operator(data, "|"));
		else if (ch == ' ' || (ch >= 9 && ch <= 13))
			return ((*data->i)--, true);
		else if (ch == '<' || ch == '>')
			return (check_redir(data));
		else if (ch == '$')
		{
			if (!expand_dollar(data))
				return (false);
		}
		else
			data->token_value[data->value_idx++] = ch;
		ch = data->input_line[++(*data->i)];
	}
	(*data->i)--;
	return (true);
}
