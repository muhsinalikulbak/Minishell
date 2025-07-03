/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:43:49 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/03 02:54:15 by muhsin           ###   ########.fr       */
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
	char	*line;
	char	*expand;
	char	*temp;
	int		i;
	int		j;

	if (check_one_dollar(data))
		return (true);
	line = data->input_line;
	i = (*data->i);
	i++;
	j = 0;
	var = (char *)ft_calloc(data->input_length + 1, sizeof(char));
	if (!var)
		return (false);
	while (line[i] && data->inv_map[(int)line[i]] == 0)
	{
		var[j] = line[i++];
		j++;
	}
	var[j] = '\0';
	expand = get_env_var_content(data->env_map, var);
	free(var);
	if (expand == NULL)
	{
		(*data->i) = i;
		printf("env variable yok frame = check_dolar\n");
		return (true);
	}
	data->token_value[*data->i] = '\0';
	temp = data->token_value;
	data->token_value = (char *)ft_calloc(data->input_length + ft_strlen(expand), sizeof(char));
	data->value_idx = 0;
	j = 0;
	while (temp[data->value_idx])
	{
		data->token_value[data->value_idx] = temp[data->value_idx];
		data->value_idx++;
	}
	while (expand[j])
	{
		data->token_value[data->value_idx] = expand[j];
		data->value_idx++;
		j++;
	}
	(*data->i) = --i;
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
			return (tokenize_operator(data, "|"));
		else if (ch == ' ' || (ch >= 9 && ch <= 13))
			return ((*data->i)--, true);
		else if (ch == '<' || ch == '>')
			return (check_redir(data));
		else if (ch == '$')
		{
			if (!check_dollar(data))
				return (false);
		}
		else
			data->token_value[data->value_idx++] = ch;
		ch = data->input_line[++(*data->i)];
	}
	(*data->i)--;
	return (true);
}
