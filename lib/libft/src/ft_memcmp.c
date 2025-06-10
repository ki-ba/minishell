/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:55:41 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/09 11:14:39 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
			return (1);
		else if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
			return (-1);
		++i;
	}
	return (0);
}
