/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omakbas <omakbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:18:39 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/07 21:50:09 by omakbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_word_tokens(t_token *start, t_token *end)
{
    t_token *current;
    int count;
    bool skip_next;

    if (!start)
        return (0);

    current = start;
    count = 0;
    skip_next = false;

    while (current && current != end)
    {
        if (skip_next)
        {
            skip_next = false;  // Skip this token (it's a redirection filename)
        }
        else if (is_redirection_token(current->type))
        {
            skip_next = true;   // Next token will be the filename, skip it
        }
        else if (current->type == TOKEN_WORD)
        {
            count++;
        }
        current = current->next;
    }

    return (count);
}

// Helper function - add to parser_utils.c
bool is_redirection_token(t_token_type type)
{
    return (type == TOKEN_REDIR_IN || 
            type == TOKEN_REDIR_OUT || 
            type == TOKEN_APPEND || 
            type == TOKEN_HEREDOC);
}

t_redir *create_redirection(t_token *redir_token, t_token *file_token)
{
    t_redir *redir;
    
    if (!redir_token || !file_token || !is_redirection_token(redir_token->type))
        return (NULL);
    
    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    
    redir->type = redir_token->type;
    redir->state = STATE_NORMAL;  // Store the state of filename token
    redir->filename = ft_strdup(file_token->value);
    if (!redir->filename)
    {
        free(redir);
        return (NULL);
    }
    
    redir->next = NULL;
    return (redir);
}

void add_redirection_to_cmd(t_cmd *cmd, t_redir *redir)
{
    t_redir *current;
    
    if (!cmd || !redir)
        return;
    
    if (!cmd->redirections)
    {
        cmd->redirections = redir;
        return;
    }
    
    // Add to end of redirection list
    current = cmd->redirections;
    while (current->next)
        current = current->next;
    
    current->next = redir;
}

void free_redirections(t_redir *redirections)
{
    t_redir *current;
    t_redir *next;
    
    current = redirections;
    while (current)
    {
        next = current->next;
        if (current->filename)
            free(current->filename);
        free(current);
        current = next;
    }
}

void print_redirections(t_redir *redirections)
{
    t_redir *current;
    
    current = redirections;
    while (current)
    {
        printf("[");
        switch (current->type)
        {
            case TOKEN_REDIR_IN:
                printf("< %s", current->filename);
                break;
            case TOKEN_REDIR_OUT:
                printf("> %s", current->filename);
                break;
            case TOKEN_APPEND:
                printf(">> %s", current->filename);
                break;
            case TOKEN_HEREDOC:
                printf("<< %s", current->filename);
                break;
            default:
                printf("unknown redirection");
        }
        printf("]");
        
        if (current->next)
            printf(" ");
        current = current->next;
    }
}

void free_commands(t_cmd *commands)
{
    t_cmd *current;
    t_cmd *next;
    int i;
    
    current = commands;
    while (current)
    {
        next = current->next;
        
        // Free arguments array
        if (current->args)
        {
            i = 0;
            while (current->args[i])
            {
                free(current->args[i]);
                i++;
            }
            free(current->args);
        }
        
        // Free redirections
        if (current->redirections)
            free_redirections(current->redirections);
        
        free(current);
        current = next;
    }
}

char **create_arg_mat(int arg_count)
{
    char **arg_matrix;
    int i;

    if (arg_count <= 0)
        return (NULL);

    // Allocate array of string pointers (+1 for NULL terminator)
    arg_matrix = (char **)malloc(sizeof(char *) * (arg_count + 1));
    if (!arg_matrix)
    {
        printf("Error: Memory allocation failed for argument matrix\n");
        return (NULL);
    }

    // Initialize all pointers to NULL
    i = 0;
    while (i <= arg_count)  // Include the extra slot for NULL terminator
    {
        arg_matrix[i] = NULL;
        i++;
    }

    return (arg_matrix);
}