/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:17:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/05 11:21:36 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_no_expand(t_lexer_data *data)
{
	char	*line;
	int		i;

	i = (*data->i);
	line = data->input_line;
	if (data->token && *data->token && get_last_token(*data->token)->type == TOKEN_HEREDOC)
	{
		data->token_value[data->value_idx++] = '$';
		return (true);
	}
	if (line[i] && (data->inv_map[(int)line[i + 1]] || line[i + 1] == '\0'))
	{
		data->token_value[data->value_idx++] = '$';
		return (true);
	}
	return (false);
}

static char	*get_value(t_lexer_data *data) // Burası bool döndürücek değer local adrese atanıcak
{
	char	*value;
	char	*line;
	char	*key;
	int		j;

	line = data->input_line;
	j = ++(*data->i);
	while (line[j] && data->inv_map[(int)line[j]] == 0)
		j++;
	key = ft_substr(data->input_line, *data->i, j - *data->i);
	value = try_get_value(data->env_map, key);
	free(key);
	key = NULL;
	*data->i = --j;
	if (value == NULL)
		return (NULL);
	return (value); // BOOL döndür local adrese atama yap
}

bool	expand_dollar(t_lexer_data *data)
{
	char	*value;
	char	*temp;
	int		j;

	if (check_no_expand(data))
		return (true);
	value = get_value(data);
	if (value == NULL)
		return (true);
	data->token_value[data->value_idx] = '\0';
	temp = data->token_value;
	data->input_length += ft_strlen(value);
	data->token_value = (char *)ft_calloc(data->input_length + 1, sizeof(char));
	ft_memmove(data->token_value, temp, ft_strlen(temp));
	data->value_idx = ft_strlen(temp);
	j = -1;
	while (value[++j])
		data->token_value[data->value_idx++] = value[j];
	return (free(temp), true);
}
