/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:48:37 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/15 17:35:42 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

int main (int argc, char **argv, char **env)
{
    char *str = ft_strdup("Merhaba"); // Bu main process'de ve adresi 0x567 olsun

    int pid = fork();

    if (pid == 0)
    {
        // Burada da str 0x567'dir
        int x;
        str[0] = 'A'; // Eğer veride değişiklik olursa fiziksel adres yine 0x567'yi gösterir ama arka planda
        // fiziksel adres değişmiş olur
        
        // Yani veri değiştirildiği an child process'de str için yeni fiziksel bir yer açılır fakat gözüken adres main'dekidir
        // O yüzden main'den  child'e geçen memory address'lere  virtual address space denir.
        // Str main process'den gelmiş olsa bile free edilmedilir. Veriyi değiştirsede değiştirmesede free edilmelidir.
        // Child process veriyi değiştirsin ya da değiştirmesin  free'lenmeden sonlandığı durumda leak çıkacaktır.
        // Veriyi değiştirip free ederse değişiklik olduğundan kendi açtığı fiziksel adres'i free'ler
        // Veriyi değiştirmeden free ederse virtual address'i freeler
        // Free edilmezse child process çıkarken bunu leak olarak algılar (bu free main'e etki etmez) 

        printf("Child : %s\n",str);
        free(str);
    }
    else
    {
        waitpid(pid, NULL, -1);
        sleep(2);
        printf("Main : %s\n",str);
        free(str);
    }

    return 0;
}
