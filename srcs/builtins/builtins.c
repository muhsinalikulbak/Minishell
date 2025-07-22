#include "minishell.h"

void echo(char *str)
{
    ft_putendl_fd(str, 0);
}

void cd(char *path, t_map **env_map_head)
{    
    char *pwd;
    char *old_pwd;
    
    if (!path)
    {
        printf("bash: cd: missing argument\n");
        return;
    }
    old_pwd = getcwd(NULL, 0);
    export(env_map_head, old_pwd, "OLDPWD", true);
    if (chdir(path) == -1)
    {
        perror("bash: cd");
        return;
    }
    pwd = getcwd(NULL, 0);
    export(env_map_head, pwd, "PWD", true);
    if (pwd)
    {
        printf("current dir: %s\n", pwd);
        free(pwd);
    }
    else
        perror("bash: getcwd");
}
void pwd(char *pwd)
{
    pwd = getcwd(NULL, 0);
    printf("pwd: %s\n",pwd);
    free(pwd);
}

void export(t_map **env_map_head, char *var, char *key, bool is_set)
{
    int size;

    if (!env_map_head || !*env_map_head)
        return;

    size = ft_mapsize(*env_map_head);

    if(is_set)
        set_var(env_map_head, key, var);
    else
        print_export(env_map_head, size);
}

void unset(t_map **env_map_head, char *key)
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
            free_map_node(current);
            printf("bash: unset: %s: successfully removed\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("bash: unset: %s: not found\n", key);
}
void env(t_map *map)
{
    print_map(map); 
}
void ft_exit()
{
    exit(get_exit_code());
}
