/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:17:28 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/04 19:38:19 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_no_expand(t_lexer_data *data)
{
	char	*line;
	int		i;

	i = (*data->i);
	line = data->input_line;
	if ((*data->token) && get_last_token(*data->token)->type == TOKEN_HEREDOC)
	{
		data->token_value[data->value_idx++] = '$';
		return (true);
	}
	if (data->inv_map[(int)line[i + 1]] || line[i + 1] == '\0')
	{
		data->token_value[data->value_idx++] = '$';
		return (true);
	}
	return (false);
}
 
bool	expand_dollar(t_lexer_data *data)
{
	char	*var;
	char	*line;
	char	*expand_value;
	char	*temp;
	int		i;
	int		j;

	if (check_no_expand(data))
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
	expand_value = try_get_value(data->env_map, var);
	free(var);
	if (expand_value == NULL)
	{
		(*data->i) = i;
		printf("env variable yok frame = check_dolar\n");
		return (true);
	}
	data->token_value[data->value_idx] = '\0';
	temp = data->token_value;
	data->token_value = (char *)ft_calloc(data->input_length + ft_strlen(expand_value), sizeof(char) + 1);
	data->value_idx = 0;
	j = 0;
	while (temp[data->value_idx])
	{
		data->token_value[data->value_idx] = temp[data->value_idx];
		data->value_idx++;
	}
	free(temp);
	while (expand_value[j])
	{
		data->token_value[data->value_idx] = expand_value[j];
		data->value_idx++;
		j++;
	}
	(*data->i) = i - 1;
	return (true);
}
