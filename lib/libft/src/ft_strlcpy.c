/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:35:21 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/09 11:15:51 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	src_len = ft_strlen(src);
	if (size <= 0)
		return (src_len);
	while (i < size - 1 && i < src_len)
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (src_len);
}
