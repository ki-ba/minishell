/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:27:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/09 11:14:43 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_uc;

	if (!dest || !src)
		return (NULL);
	dest_uc = (unsigned char *)dest;
	i = 0;
	if (dest == src)
		return (0);
	while (i < n)
	{
		dest_uc[i] = ((unsigned char *)src)[i];
		++i;
	}
	return (dest);
}
