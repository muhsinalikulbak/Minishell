/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:17:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/18 21:34:37 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_no_expand_for_token(t_lexer_data *data)
{
	t_token	*last;
	char	*line;
	int		i;

	last = get_last_token(*data->token);
	if (last && last->type == TOKEN_HEREDOC)
	{
		data->token_value[data->value_idx++] = '$';
		return (true);
	}
	i = (*data->i);
	line = data->input_line;
	if (line[i + 1] != '_' && (!ft_isalnum(line[i + 1]) || !line[i + 1]))
	{
		data->token_value[data->value_idx++] = '$';
		return (true);
	}
	return (false);
}

static bool	get_value_for_token(t_lexer_data *data, char **value)
{
	char	*line;
	char	*key;
	int		j;

	line = data->input_line;
	j = ++(*data->i);
	if (ft_isdigit(line[j]))
	{
		*value = "";
		return (true);
	}
	while (line[j] && (ft_isalnum(line[j]) || line[j] == '_'))
		j++;
	key = ft_substr(data->input_line, *data->i, j - *data->i);
	if (!key)
	{
		ft_putendl_fd("memory allocation failed", 2);
		return (false);
	}
	*value = try_get_value(key);
	free(key);
	*data->i = --j;
	return (true);
}

bool	expand_dollar(t_lexer_data *data)
{
	char	*value;
	char	*temp;
	int		j;

	if (check_no_expand_for_token(data))
		return (true);
	if (!get_value_for_token(data, &value))
		return (false);
	if (value == NULL)
		return (true);
	data->token_value[data->value_idx] = '\0';
	temp = data->token_value;
	data->input_length += ft_strlen(value);
	data->token_value = (char *)ft_calloc(data->input_length + 1, sizeof(char));
	if (!data->token_value)
	{
		ft_putendl_fd("memory allocation failed", 2);
		return (free(temp), false);
	}
	ft_memmove(data->token_value, temp, ft_strlen(temp));
	data->value_idx = ft_strlen(temp);
	j = -1;
	while (value[++j])
		data->token_value[data->value_idx++] = value[j];
	return (free(temp), true);
}
