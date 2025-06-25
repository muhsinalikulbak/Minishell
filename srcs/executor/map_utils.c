#include "minishell.h"

t_map *mat_to_map(char **mat)
{
    int i;
    int j;
    char *key;
    char *content;
    int key_len;
    int content_len;
    int content_start;
    t_map *head;
    t_map *tmp;

    head = NULL;
    i = 0;
    while (mat[i])
    {
        j = 0;
        key_len = 0;
        while (mat[i][j] != '=')
            j++;
        key_len = j;
        key = ft_substr(mat[i], 0, key_len);
        content_len = ft_strlen(mat[i]) - key_len - 1;
        content_start = key_len + 1;
        content = ft_substr(mat[i], content_start, content_len);
        if (!head)
            head = create_map(key, content);
        else
        {
            tmp = create_map(key, content);
            ft_map_add_back(&head, tmp);
        }
            
        i++;
    }
    print_map(head);
    return head;
}

t_map	*create_map(char *key, char *content)
{
	t_map	*new_node;

	new_node = malloc(sizeof(t_map));
	if (!new_node)
		return (NULL);
	new_node->content = content;
    new_node->key = key;
	new_node->next = NULL;
	return (new_node);
}

void	ft_map_add_back(t_map **map, t_map *new)
{
	t_map	*last;

	last = ft_maplast(*map);
	if (!last)
	{
		*map = new;
		return ;
	}
	last->next = new;
}

t_map	*ft_maplast(t_map *map)
{
	if (!map)
		return (NULL);
	while (map->next != NULL)
	{
		map = map->next;
	}
	return (map);
}

int	ft_mapsize(t_map *map)
{
	int	count;

	count = 0;
	while (map != NULL)
	{
		count++;
		map = map->next;
	}
	return (count);
}

void print_map(t_map *map)
{
	t_map *ptr;
	if (!map)
	{
		printf("Empty token map\n");
		return;
	}
	ptr = map;
	printf("TOKEN map:\n");
	while (ptr)
	{
		printf("%s=", ptr->key);
        printf("%s\n", ptr->content);
		ptr = ptr->next; 
	}
	printf("\n");
}

void free_map(t_map *map)
{
	t_map *head;
    t_map *tmp;
	if (!map)
	{
		printf("Empty token map\n");
		return;
	}
	head = map;
	while (head)
	{   
        while (tmp->next)
            tmp = tmp->next;
        free(tmp->content);
        free(tmp->key);
        free(tmp);
        if (!head)
            tmp = head; 
	}
    tmp = NULL;
    head = NULL;
}