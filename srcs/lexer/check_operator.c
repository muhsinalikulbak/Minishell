/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:43:49 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/02 03:53:59 by muhsin           ###   ########.fr       */
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

static bool	tokenize_operator(t_lexer_data *data, char *operator)
{
	int	len;

	data->token_value[data->value_idx] = '\0';
	len = ft_strlen(data->token_value);
	if (len == 0)
		free(data->token_value);
	else
		tokenize(data, data->token);
	data->token_value = ft_strdup(operator);
	if (data->token_value == NULL)
		return (false);
	data->prev_state = data->state;
	data->state = STATE_IDLE;
	tokenize(data, data->token); 
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

bool	check_dollar(t_lexer_data *data)
{
	char	*var;
	char	*map;
	char	*line;
	char	ch;
	int		i;
	int		j;

	if (get_last_token(*data->token)->type == TOKEN_HEREDOC)
	{
		data->token_value[data->value_idx++] = '$';
		return (true);
	}
	map = (char *)ft_calloc(256, 1); // state_init'de bunu initleyip struct'a verip, oradan kullanabilirim.
	if (!map)
		return (false);
	punc_map_init(map);
	i = *data->i;
	line = data->input_line;
	ch = line[i + 1];
	if (map[(int)ch] || ch == ' ' || ch == '\0')
	{
		data->token_value[data->value_idx++] = '$';
		free(map);
		return (true);
	}
	i++;
	var = (char *)ft_calloc(data->input_length + 1, sizeof(char));
	while (line[i] && map[(int)line[i]] == 0)
	{
		var[j] = line[i++];
		j++;
	}
	var[j] = '\0';
	i--;
	return (true);
	//BURADA EXPAND EDİLİCEK
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
		{
			(*data->i)--;
			return (true);
		}
		else if (ch == '<' || ch == '>')
			return (check_redir(data));
		else if (ch == '$' && !check_dollar(data))
			return (false);
		else
			data->token_value[data->value_idx++] = ch;
		ch = data->input_line[++(*data->i)];
	}
	(*data->i)--;
	return (true);
}
