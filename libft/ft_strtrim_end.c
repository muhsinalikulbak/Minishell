/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhsin <muhsin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:05:43 by muhsin            #+#    #+#             */
/*   Updated: 2025/07/23 11:09:29 by muhsin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_end(char const *s1, char const *set)
{
	size_t	end;
	char	*result;
	int		*map;

	map = (int *)ft_calloc(256, sizeof(int));
	if (!map)
		return (NULL);
	while (*set)
	{
		map[(int)*set] = -1;
		set++;
	}
	end = ft_strlen(s1) - 1 ;
	while (s1[end] && map[(int)s1[end]] == -1)
		end--;
	result = ft_substr(s1, 0, end + 1);
	free(map);
	return (result);
}
