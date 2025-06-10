/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:32:10 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/07 18:17:20 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*dup;
	size_t	size;

	if (!s)
		return (NULL);
	size = (ft_strlen(s)+1) * (sizeof(char));
	dup = malloc(size);
	if (!dup)
		return (0);
	ft_strlcpy(dup, s, size);
	return (dup);
}
