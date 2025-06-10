/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:41:02 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/07 18:19:39 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*sub;

	if (!s)
		return (NULL);
	i = 0;
	if (start > ft_strlen(s))
		size = 1;
	else
		size = (ft_strnlen(s + start, len) + 1);
	sub = malloc(size);
	if (!sub)
		return (0);
	while (i < size - 1)
	{
		sub[i] = s[start + i];
		++i;
	}
	sub[i] = '\0';
	return (sub);
}
