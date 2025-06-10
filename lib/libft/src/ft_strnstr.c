/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:50:49 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/09 11:16:12 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char big[], const char little[], size_t len)
{
	size_t	i;
	size_t	j;
	size_t	big_len;
	size_t	lil_len;

	if (!big || !little)
		return (NULL);
	big_len = ft_strnlen((char *)big, len);
	lil_len = ft_strlen((char *)little);
	if (lil_len == 0)
		return ((char *)big);
	i = 0;
	while (i < big_len)
	{
		j = 0;
		while (i + j < big_len && big[i + j] == little[j])
		{
			if (j == lil_len - 1)
				return ((char *)&(big[i]));
			++j;
		}
		++i;
	}
	return (0);
}
