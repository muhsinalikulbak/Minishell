/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:04:23 by muhsin            #+#    #+#             */
/*   Updated: 2025/06/16 03:02:15 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_token_type
{
	TOKEN_COMMAND,
	TOKEN_COMMENT,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}		t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_simple_command
{
	t_token	*cmd_head;
}		t_command;

typedef struct s_io_redir
{
	char	*outfile;
	char	*infile;
	char	*errorfile;
}		t_io_redir;

t_token	*lexer(char *command_line);
void	syntax_chck(char **tokenized_cmd);
void	scan(char *input_cmd, t_token **token);
bool	anlayse(char *cmd, t_token **token);

//Token Utils
void	insert_token(t_token **head, char *val, t_token_type token_type);
void	free_list(t_token **list);
void	print_list(t_token *list);
int		ft_num_of_tokens(t_token *list);
#endif