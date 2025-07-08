/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:52:32 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/07 21:47:57 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser(t_token *token_list)
{
	t_cmd	*cmd_head;
	t_cmd	*cmd_ptr;
	// t_token *ptr; Şu an kullanılmıyor diye yorum satırına aldım.
	t_token *head;
	t_token *tail;

	if(!token_list)
	{
		printf("token list is emty (message from parser)\n");
		return NULL;
	}
	
	if (!syntax_check(token_list))
		return (NULL);	
	// ptr = token_list; Şu an kullanılmıyor diye yorum satırına aldım.
	head = token_list;
	tail = token_list;
	cmd_head = NULL;
	
	while (tail->next)
	{
		if(tail->type == TOKEN_PIPE)
		{
			if (!cmd_head)
			{
				cmd_head = new_cmd(head, tail);
				cmd_ptr = cmd_head;
			}	
			else
				cmd_ptr = new_cmd(head, tail);
				
			cmd_ptr = cmd_ptr->next;
			head = tail;
		}
		tail = tail->next;
	}
	cmd_ptr->next = new_cmd(head, tail);
	free_token(&token_list);
	return (cmd_head);
}

t_cmd *new_cmd(t_token *start, t_token *end)
{
    t_token *ptr;
    t_cmd *cmd;
    int arg_count;
    int i;
    bool skip_next;

    arg_count = count_word_tokens(start, end);
    
    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    
    // Initialize command structure
    cmd->args = create_arg_mat(arg_count);
    if (!cmd->args)
    {
        free(cmd);
        return (NULL);
    }
    
    cmd->redirections = NULL;  // Initialize redirections
    cmd->next = NULL;
    
    // Parse arguments and redirections
    ptr = start;
    i = 0;
    skip_next = false;
    
    while (ptr != end && ptr)
    {
        if (skip_next)
        {
            skip_next = false;
        }
        else if (is_redirection_token(ptr->type))
        {
            // Create and add redirection
            t_redir *redir = create_redirection(ptr, ptr->next);
            if (redir)
                add_redirection_to_cmd(cmd, redir);
            skip_next = true;  // Skip the filename token
        }
        else if (ptr->type == TOKEN_WORD)
        {
            if (i < arg_count)
            {
                cmd->args[i] = ft_strdup(ptr->value);
                i++;
            }
        }
        ptr = ptr->next;
    }
    
    return (cmd);
}



void print_parser(t_cmd *parsed_list)
{
    t_cmd *ptr;
    int cmd_num;
    int i;

    if (!parsed_list)
    {
        printf("Nothing in parsed list\n");
        return;
    }
    
    ptr = parsed_list;
    cmd_num = 0;
    
    while (ptr)
    {
        printf("CMD[%d]: ", cmd_num);
        
        if (ptr->args)
        {
            i = 0;
            while (ptr->args[i])
            {
                printf("%s ", ptr->args[i]);
                i++;
            }
        }
        
        if (ptr->redirections)
        {
            printf("| Redirections: ");
            print_redirections(ptr->redirections);
        }
        
        printf("\n");
        ptr = ptr->next;
        cmd_num++;
    }
}