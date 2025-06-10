/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:13:24 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/07 18:54:27 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (!s || !f)
		return (0);
	i = 0;
	while (i < ft_strlen(s))
	{
		f(i, &s[i]);
		++i;
	}
	return (s);
}
