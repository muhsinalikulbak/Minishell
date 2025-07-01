#include "minishell.h"

bool validate_key(char *key)
{
    int i;
    
    if (!key)
        return false;
        
    i = 0;
    while (key[i])
    {
        if (ft_isalpha(key[i]) == 0 && key[0] != '_')
            return false;
        i++;
    }
    
    return true;
}

void add_new_var(t_map **env_map_head, char *key, char *var)
{
    t_map *tmp;
    
    tmp = create_map(ft_strdup(key), ft_strdup(var));
    ft_map_add_back(env_map_head, tmp);
}
void set_var(t_map **env_map_head, char *key, char *var)
{
    if (update_existing_var(env_map_head, key, var))
        return;
    
    if (!key)
    {
        printf("bash: %s not found\n", var);
        set_exit_code(130);
        return;
    }
    
    if (!validate_key(key))
    {
        printf("bash: export: '%s': not a valid identifier\n", key);
        set_exit_code(130);
        return;
    }
    
    add_new_var(env_map_head, key, var);
}

static t_map *find_smallest_unprinted_key(t_map **env_map_head, char **printed_keys)
{
    t_map *ptr;
    t_map *smallest;
    
    smallest = NULL;
    ptr = *env_map_head;
    
    while (ptr)
    {
        if (!is_key_in_array(printed_keys, ptr->key) && 
            (!smallest || ft_strcmp(ptr->key, smallest->key) < 0))
            smallest = ptr;
        ptr = ptr->next;
    }
    
    return smallest;
}
static void print_and_track_key(t_map *map, char **printed_keys, int index)
{
    if (map)
    {
        printf("declare -x %s=%s\n", map->key, map->content);
        printed_keys[index] = ft_strdup(map->key);
    }
}
void print_export(t_map **env_map_head, int size)
{
    // t_map *ptr;  ŞU AN KULLANILMIYOR UNUSED HATASI ALIYOR
    t_map *smallest;
    char **printed_keys;
    int i;
   
    i = 0;
    printed_keys = (char **)ft_calloc((size + 1), sizeof(char *));
    smallest = NULL;
    
    if (!printed_keys)
        return;
        
    while (i < size)
    {   
        smallest = find_smallest_unprinted_key(env_map_head, printed_keys);
        print_and_track_key(smallest, printed_keys, i);
        i++;
    }
    free_mat(printed_keys, size);
}