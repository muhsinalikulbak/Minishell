/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kayraakbas <kayraakbas@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:57:07 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/06/17 22:22:05 by kayraakbas       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// implement lexical Analyser in pdf 

#include "minishell.h"

t_token	*get_last_token(t_token *head)
{	
	if (head == NULL)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

void insert_token(t_token **head, char* val, t_token_type token_type)
{
	t_token *new_token;
	t_token	*last;

	new_token = (t_token *)malloc(sizeof(t_token));

	if (new_token == NULL)
	{
		perror("failed to allocate new token - failed in insert_token func\n");
		return;
	}
	new_token->value = ft_strdup(val);
	new_token->type = token_type;
	new_token->next = NULL;
	new_token->prev = NULL;
	last = get_last_token(*head);
	if (last == NULL)
		*head = new_token;
	else
	{
		last->next = new_token;
		new_token->prev = last;
	}
}

void free_list(t_token **list)
{
	t_token *current;
	t_token *next;

	if (!list || !*list)
	{
		printf("List is empty can not be freed\n");
		return;
	}
	current = *list;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*list = NULL;
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
		printf("<%s> ", ptr->value);
		ptr = ptr->next; 
	}
	
}

int ft_num_of_tokens(t_token *list)
{
	t_token *ptr;
	int len;
	if(list == NULL)
	{
		perror("list is not exist. num_of_tokens: N/A\n");
		return 0;
	}
	ptr = list;
	len = 0;
	while (ptr)
	{
		ptr = ptr->next;
		len++;
	}
	printf("lenght of tokens: %d\n", len);
	return (len);
}
