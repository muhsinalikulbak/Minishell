/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:17:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/08/07 18:24:17 by muhsin           ###   ########.fr       */
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
	data->expanding = true;
	return (false);
}

static bool	expand_special_param(char **value, char ch, bool *is_it_exit_code)
{
	if (ft_isdigit(ch))
		*value = "";
	else if (ch == '?')
	{
		*value = ft_itoa(get_exit_code());
		if (!*value)
		{
			ft_putendl_fd("memory allocation failed", 2);
			return (false);
		}
		*is_it_exit_code = true;
	}
	return (true);
}

static bool	get_value_for_token(t_lexer_data *data, char **value,
		bool *is_it_exit_code)
{
	char	*line;
	char	*key;
	int		j;

	*is_it_exit_code = false;
	line = data->input_line;
	j = ++(*data->i);
	if (line[j] == '?' || ft_isdigit(line[j]))
		return (expand_special_param(value, line[j], is_it_exit_code));
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
	return (free(key), true);
}

static void	realloc_token_value(t_lexer_data *data, char *temp_value,
		char *value)
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
		if (is_it_exit_code)
			free(value);
		return (free(temp_value), false);
	}
	realloc_token_value(data, temp_value, value);
	if (is_it_exit_code)
		free(value);
	return (free(temp_value), true);
}
