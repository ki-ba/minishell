/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:54:05 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/09 11:14:50 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*start;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	start = (char *)s;
	while (i < n)
	{
		*(start + i) = c;
		++i;
	}
	return (start);
}
