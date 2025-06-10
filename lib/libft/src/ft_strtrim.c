/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:24:17 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/07 18:18:19 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*s2;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	if (!end)
		++end;
	while (ft_is_in(s1[start], set) && start < ft_strlen(s1))
		++start;
	while (ft_is_in(s1[end], set) && end > start)
		--end;
	s2 = ft_substr(s1, start, end - start + 1);
	return (s2);
}
