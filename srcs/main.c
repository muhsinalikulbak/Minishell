/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/26 01:26:54 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

extern int value; // lexer.c 'de tanımlı bir global değişken

void	handle_signal(int sig)
{
printf("Ctrl+C (SIGINT) yakalandı! Kod: %d\n", sig);
}

int main (int argc, char **argv, char **env)
{
	// signal(SIGINT, handle_signal);
	// // print(value); Lexer.c deki global değişken value'yu yazdırır.
	// while(1)
	// {
	// 	printf("Çalışıyor\n");
	// 	sleep(1);
	// }
	int fd = open("file", O_CREAT | O_RDWR, 0644);
	if (fd == -1)
	{
		printf("Error code : %d\n", errno);
		perror("Error");
		printf("Error : %s\n", strerror(errno));
	}
	// EISDIR = is a directory
	// EACCES = permission denied
}
