/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:17:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/29 19:42:50 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_no_expand_for_token(t_lexer_data *data)
{
	t_token	*last;
	char	*line;
	char	ch;
	int		i;

	last = get_last_token(*data->token);
	if (last && last->type == HEREDOC)
	{
		data->token_value[data->value_idx++] = '$';
		return (true);
	}
	i = (*data->i);
	line = data->input_line;
	ch = line[i + 1];
	if (ch != '_' && ch != '?' && (!ft_isalnum(ch) || !ch))
	{
		data->token_value[data->value_idx++] = '$';
		return (true);
	}
	return (false);
}

static bool	get_value_for_token(t_lexer_data *data, char **value, bool *is_it_exit_code)
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
	if (line[j] == '?')
	{
		key = ft_itoa(get_exit_code());
		if (!key)
		{
			ft_putendl_fd("memory allocation failed", 2);
			return (false);
		}
		*value = key;
		*is_it_exit_code = true;
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
	if (*value == NULL)
		data->is_ambiguous = true;
	*data->i = --j;
	*is_it_exit_code = false;
	return (free(key), true);
}

static void	realloc_token_value(t_lexer_data *data, char *temp_value, char *value)
{
	int	i;

	ft_memmove(data->token_value, temp_value, ft_strlen(temp_value));
	data->value_idx = ft_strlen(temp_value);
	i = -1;
	while (value[++i])
		data->token_value[data->value_idx++] = value[i];
}

bool	expand_dollar(t_lexer_data *data)
{
	char	*value;
	char	*temp_value;
	bool	is_it_exit_code;

	if (check_no_expand_for_token(data))
		return (true);
	if (!get_value_for_token(data, &value, &is_it_exit_code))
		return (false);
	if (value == NULL)
		return (true);
	data->token_value[data->value_idx] = '\0';
	temp_value = data->token_value;
	data->input_length += ft_strlen(value);
	data->token_value = (char *)ft_calloc(data->input_length + 1, sizeof(char));
	if (!data->token_value)
	{
		ft_putendl_fd("memory allocation failed", 2);
		return (free(temp_value), false);
	}
	realloc_token_value(data, temp_value, value);
	if (is_it_exit_code)
		free(value);
	return (free(temp_value), true);
}
