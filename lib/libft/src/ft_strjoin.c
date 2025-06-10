/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:05:55 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/07 18:55:15 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3 = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!s3)
		return (0);
	while (++i < s1_len)
		s3[i] = s1[i];
	i = -1;
	while (++i < s2_len)
		s3[s1_len + i] = s2[i];
	s3[s1_len + i] = '\0';
	return (s3);
}
