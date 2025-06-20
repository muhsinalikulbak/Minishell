/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:23 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/20 00:13:23 by muhsin           ###   ########.fr       */
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


t_token	*lexer(char *command_line);
void	insert_token(t_token **head, char *val, t_token_type token_type);
void	free_list(t_token **list);
void	print_list(t_token *list);
int		ft_num_of_tokens(t_token *list);
t_token	*get_last_token(t_token *head);
#endif