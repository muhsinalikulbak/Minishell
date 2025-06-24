/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:01:14 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/24 20:49:21 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_history(t_lexer_data *data, char *new_line)
{
	char	*temp;

	temp = data->history;
	data->history = ft_strjoin(data->history, "\n");
	free(temp);
	temp = data->history;
	data->history = ft_strjoin(data->history, new_line);
	free(temp);
}

char *get_input(bool quote_state)
{
	char *line;

	if (quote_state)
		line = readline("minishell~$ ");
	else
		line = readline("> ");
	if (!line)
		handle_eof();
	return (line);
}

char	*get_input_again(t_lexer_data *data)
{
	char	*temp;
	int		new_len;
	char	*new_line;
	bool	quote_state;

	quote_state = false;
	data->history = data->input_line;
 	
	while (!quote_state)
	{
		new_line = get_input(false);
		data->token_value[data->value_idx++] = '\n';
		data->token_value[data->value_idx] = '\0';
		
		new_len = ft_strlen(new_line);
		data->input_length = ft_strlen(new_line) + ft_strlen(data->token_value) + 10;
		temp = data->token_value;
		ft_memmove(data->token_value, temp, ft_strlen(temp));
		free(temp);

        set_history(data, new_line);
        free(data->input_line);
        data->input_line = new_line;
        quote_state = split_line(data->input_line, data);
    }
	free(new_line);
	return data->history;
}
