/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:18:53 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/07 18:19:19 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *str, size_t n)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (i < n && str[i])
		++i;
	return (i);
}
