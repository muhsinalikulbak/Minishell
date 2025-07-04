#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;

	return (s1[i] - s2[i]);
}

void free_mat(char **mat, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        if (mat[i])
            free(mat[i]);
        i++;
    }   
    free(mat);
}
void free_map_node(t_map *node)
{
    if (!node)
        return;
        
    free(node->key);
    free(node->content);
    free(node);
}

bool is_key_in_array(char **array, char *key)
{
    int i = 0;
    
    while (array[i])
    {
        if (ft_strcmp(array[i], key) == 0)
            return true;
        i++;
    }
    return false;
}

bool update_existing_var(t_map **env_map_head, char *key, char *var)
{
    t_map *tmp;
    
    if (!key || !is_key_exist(*env_map_head, key))
        return false;
        
    tmp = *env_map_head;
    while (tmp && ft_strcmp(key, tmp->key) != 0)
        tmp = tmp->next;
    
    if (tmp)
    {
        free(tmp->content);
        tmp->content = ft_strdup(var);
        return true;
    }
    return false;
}




/*
static char *get_home(t_map *env_map_head)
{
    t_map *ptr;
    char *home;

    ptr = env_map_head;
    home = NULL;

    while (ptr)
    {
        if (ft_strcmp("HOME", ptr->key) == 0)
        {
            home = ft_strdup(ptr->key);
            break;
        }   
        ptr = ptr->next;
    }
    return (home);
}
*/