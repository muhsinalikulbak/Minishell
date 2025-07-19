/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/07/20 02:12:12 by muhsin           ###   ########.fr       */
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
	signal(SIGINT, handle_signal);
	// print(value); Lexer.c deki global değişken value'yu yazdırır.
	while(1)
	{
		printf("Çalışıyor\n");
		sleep(1);
	}
}
