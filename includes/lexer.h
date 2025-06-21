/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:23 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/21 22:01:11 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_token_state
{
	STATE_NORMAL,
	STATE_IN_DQUOTE,
	STATE_IN_SQUOTE,
    STATE_IDLE
}		t_token_state;

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}		t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_state_data
{
	t_token_state	state;
	t_token_state	prev_state;
	t_token			**token;
	char			*token_value;
	char			*input_line;
	int				line_length;
	int				value_idx;
}		t_state_data;

void	lexer(t_token **token, char *command_line);
void	insert_token(t_token **token_head, t_token_type token_type, char *value);
void	free_list(t_token **list);
void	print_list(t_token *list);
int		ft_num_of_tokens(t_token *list);
t_token	*get_last_token(t_token *head);
void	state_idle(t_state_data *data, char ch);
void	state_normal(t_state_data *data, char ch);
void    tokenize(t_state_data *data, t_token **token);
void	state_double_quote(t_state_data *data, char ch);
void	state_single_quoute(t_state_data *data, char ch);
void	last_state(t_state_data *data);
#endif