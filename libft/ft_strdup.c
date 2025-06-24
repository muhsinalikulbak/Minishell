/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:47:03 by mkulbak           #+#    #+#             */
/*   Updated: 2025/06/25 01:18:26 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char	*s1)
{
	int		i;
	int		len;
	char	*heap_str;

	i = 0;
	len = ft_strlen(s1) + 1;
	heap_str = (char *)malloc(sizeof(char) * len);
	if (!heap_str)
		return (NULL);
	while (s1[i])
	{
		heap_str[i] = s1[i];
		i++;
	}
	heap_str[i] = '\0';
	return (heap_str);
}
