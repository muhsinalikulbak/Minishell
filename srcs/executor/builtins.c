#include "minishell.h"

void echo(char *str)
{
    printf("str\n");
}
void cd(char *path)
{
    char *pwd;
    chdir(path);
    pwd = getcwd(NULL, 0);
    printf("current dir: %s\n", pwd);
}
void pwd(char *pwd)
{
    pwd = getcwd(NULL, 0);
    printf("pwd: %s\n",pwd);
}
void export(char *var, char *key)
{

}
void unset(){}
void env(t_map *map)
{

}
void exit(){}