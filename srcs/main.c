/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/13 20:04:47 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

typedef union u_data
{
	int i;
	char *str;
}	t_data;

int main (int argc, char **argv, char **env)
{
  
	t_data data;
	data.i = 25;
	data.str = "Merhaba";
	printf("%s\n",data.str);
	printf("%d\n",data.i);
    return 0;
}
