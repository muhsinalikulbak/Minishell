/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:52:32 by kayraakbas        #+#    #+#             */
/*   Updated: 2025/07/22 22:38:57 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_segment	*segment(t_token *token)
{
	int	segment_count;

	segment_count = get_segment_count(token);
	t_segment	*segments = malloc(sizeof(t_segment) * segment_count);
	if (!segments)
	{
		ft_putendl_fd("memory allocation failed", 2);
		free_token(token);
		return (NULL);
	}
	if (!create_segment(token, segments, segment_count))
	{
		ft_putendl_fd("memory allocation failed", 2);
		free_token(token);
		return (NULL);
	}
	free_token(token);
	if (!heredoc_init(segments))
	{
		// heredoc da CTRL+C sinyaliyle çıkıldığında bu hata mesajı yazılmayacak.
		// CTRL+D ile çıkılırsa bash'deki hata mesajı yazılacak.
		// Sinyal dışında hata oluşmuş ise aşağıdaki hata yazılacak.
		// Bunu anlamanın yolu flag koymak. Flag'i 0 ile başlat bu hata yok anlamına gelsin.
		// CTRL+C ile çıkıldıysa Flag 1 olsun, CTRL+D olursa flag 2 olsun.
		// Hata oluştuğunda flag 3 olsun. // FLAG 3 gelirsa aşağıdaki yazılıcak.
		// Çıkış sinyalini yakalayarak bu flag atamaları yapılabilir.
		// Eğer sorun olmadan çıkarsa zaten succes döner exit kodu 0'dır.
		ft_putendl_fd("heredoc initialization failed", 2);
		return (NULL);
	}
	return (segments);
}

t_segment	*parser(t_token *token)
{
	t_segment	*segments;

	segments = segment(token);
	if (!segments)
		return (NULL);
	
	return (segments);
}
