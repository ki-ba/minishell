/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:32:20 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/09 11:14:46 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;

	if (!dest || !src)
		return (NULL);
	if ((src < dest))
	{
		i = n - 1;
		while (i >= 0)
		{
			((unsigned char *)(dest))[i] = ((unsigned char *)(src))[i];
			--i;
		}
	}
	if (dest < src)
	{
		i = 0;
		ft_memcpy(dest, src, n);
	}
	return (dest);
}
