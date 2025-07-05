/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:23 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/05 11:16:22 by muhsin           ###   ########.fr       */
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

typedef struct s_lexer_data
{
	t_token_state	state;
	t_token_state	prev_state;
	t_token			**token;
	t_map			*env_map;
	char			*token_value;
	char			*input_line;
	char			*history;
	char			*inv_map; // invalid chars map
	int				input_length;
	int				value_idx;
	int				*i;
}		t_lexer_data;

t_token	*get_last_token(t_token *head);
char	*get_input();
int		get_token_count(t_token *token);
bool	lexer(t_token **token, char *input_line, t_map *env_map);
bool	state_idle(t_lexer_data *data);
bool	state_normal(t_lexer_data *data, char ch);
bool	last_state(t_lexer_data *data);
bool	check_operator(t_lexer_data *data);
void	free_token(t_token **list);
void	print_token_list(t_token *list);
void    tokenizer(t_lexer_data *data, t_token **token);
void	state_double_quote(t_lexer_data *data, char ch);
void	state_single_quoute(t_lexer_data *data, char ch);
void	past_space(t_lexer_data *data);
void	print_redir_error(char *line, int i);
bool	expand_dollar(t_lexer_data *data);
#endif