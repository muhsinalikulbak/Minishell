/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 01:32:14 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/03 02:48:10 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	past_space(t_lexer_data *data)
{
	char	ch;

	ch = data->input_line[*data->i];
	while (ch)
	{
		if (ch != ' ' && !(ch >= 9 && ch <= 13))
			break ;
		ch = data->input_line[++(*data->i)];
	}
	if (ch == '\0')
	{
		free(data->token_value);
		data->token_value = NULL;
	}
}

void	print_redir_error(char *line, int i)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	if (line[i] != line[i + 1])
		ft_putendl_fd(&line[i + 1], 2);
	else
		ft_putendl_fd(&line[i + 2], 2);
}

void	init_inv_map(int *map)
{
	int	ch;

	ch = ' ';
	while (ch <= '/')
		map[ch++]++;
	ch = ':';
	while (ch <= '@')
		map[ch++]++;
	ch = '[';
	while (ch <= '`')
		map[ch++]++;
	ch = '{';
	while (ch <= '~')
		map[ch++]++;
}

 bool	check_one_dollar(t_lexer_data *data)
 {
	char	*line;
	int		i;

	if (get_last_token(*data->token)->type == TOKEN_HEREDOC)
	{
		data->token_value[data->value_idx++] = '$';
		return (true);
	}
	i = (*data->i);
	line = data->input_line;
	if (data->inv_map[(int)line[i + 1]] || line[i + 1] == '\0')
	{
		data->token_value[data->value_idx++] = '$';
		return (true);
	}
	return (false);
 }
