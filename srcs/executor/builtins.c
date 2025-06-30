#include "minishell.h"


void echo(char *str)
{
    (void) str;
    ft_putendl_fd(str, 0);
}
static int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;

	return (s1[i] - s2[i]);
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
void cd(char *path)
{    
    char *pwd;
    if (!path)
    {
        printf("bash: cd: missing argument\n");
        return;
    }
    if (chdir(path) == -1)
    {
        perror("bash: cd");
        return;
    }
    pwd = getcwd(NULL, 0);

    if (pwd)
    {
        printf("current dir: %s\n", pwd);
        free(pwd);
    }
    else
    {
        perror("bash: getcwd");
    }
}
void pwd(char *pwd)
{
    pwd = getcwd(NULL, 0);
    printf("pwd: %s\n",pwd);
}

static bool is_key_in_array(char **array, char *key)
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
void export(t_map **env_map_head, char *var, char *key, bool is_set)
{
    t_map *tmp;
    t_map *ptr;
    t_map *smallest;
    char **printed_keys;
    int size;
    int i;

    if (!env_map_head || !*env_map_head)
        return;

    smallest = NULL;
    size = ft_mapsize(*env_map_head);
    
    if(is_set)
    {
        if(key && is_key_exist(*env_map_head, key))
        {
            tmp = *env_map_head;
            while (tmp && ft_strcmp(key, tmp->key) != 0)
                tmp = tmp->next;
            
            if (tmp)
            {
                free(tmp->content);
                tmp->content = ft_strdup(var);
            }
        }
        else
        {
            if(!key)
            {
                printf("bash: %s not found\n",var);
                exit(130);
            }
            i = 0;
            while (key[i])
            {
                if (ft_isalpha(key[i]) == 0 && key[0] != '_')
                {
                    printf("bash: export: '%s': not a valid identifier\n",key);
                    exit(130);
                }
                i++;
            }
            tmp = create_map(ft_strdup(key), ft_strdup(var));
            ft_map_add_back(env_map_head, tmp);
        }
    }
    else
    {
        printed_keys = (char **)ft_calloc((size + 1), sizeof(char *));
        if (!printed_keys)
            return;

        i = 0;
        while (i < size)
        {
            smallest = NULL;
            ptr = *env_map_head;
            
            while (ptr)
            {
                if (!is_key_in_array(printed_keys, ptr->key) && 
                    (!smallest || ft_strcmp(ptr->key, smallest->key) < 0))
                    smallest = ptr;
                
                ptr = ptr->next;
            }
            
            if (smallest)
            {
                printf("declare -x %s=%s\n", smallest->key, smallest->content);
                printed_keys[i] = ft_strdup(smallest->key);
            }
            i++;
        }
        i = 0;
        while (i < size)
        {
            if (printed_keys[i])
                free(printed_keys[i]);
            i++;
        }
        free(printed_keys);
    }
}

void ft_unset(t_map **env_map_head, char *key)
{
    t_map *current;
    t_map *prev;

    if (!env_map_head || !*env_map_head || !key)
        return;

    current = *env_map_head;
    prev = NULL;

    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env_map_head = current->next;

            free(current->key);
            free(current->content);
            free(current);
            printf("bash: unset: %s: successfully removed\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("bash: unset: %s: not found\n", key);
}
void ft_env(t_map *map)
{
    print_map(map); 
}
void ft_exit()
{
    exit(get_exit_code());
}