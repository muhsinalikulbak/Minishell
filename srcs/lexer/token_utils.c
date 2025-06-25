/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:57:07 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/26 01:44:31 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// implement lexical Analyser in pdf 

#include "minishell.h"

t_token	*get_last_token(t_token *token_head)
{	
	if (token_head == NULL)
		return (NULL);
	while (token_head->next != NULL)
		token_head = token_head->next;
	return (token_head);
}

void insert_token(t_token **token_head, t_token_type token_type, char *value)
{
	t_token *new_token;
	t_token	*last;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
	{
		perror("failed to allocate new token - failed in insert_token func\n");
		return;
	}
	new_token->value = value;
	new_token->type = token_type;
	new_token->next = NULL;
	new_token->prev = NULL;
	last = get_last_token(*token_head);
	if (last == NULL)
		*token_head = new_token;
	else
	{
		last->next = new_token;
		new_token->prev = last;
	}
}

void free_token(t_token **token_head)
{
	t_token *current;
	t_token *next;

	if (!token_head || !*token_head)
		return;
	current = *token_head;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void print_list(t_token *list)
{
	t_token *ptr;
	if (!list)
	{
		printf("Empty token list\n");
		return;
	}
	ptr = list;
	printf("TOKEN LIST:\n");
	while (ptr)
	{
		write(1, "<", 1);
		write(1, ptr->value, ft_strlen(ptr->value));
		write(1, ">", 1);
		write(1, " ", 1);
		ptr = ptr->next; 
	}
	printf("\n");
}
