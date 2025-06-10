/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_random_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:05:42 by kiba              #+#    #+#             */
/*   Updated: 2025/03/10 12:21:05 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	@brief creates a pseudo-random string of `len`
 *	@brief length on the heap.
 *	@param len the length of the string to create
 *	@returns the pseudo-random string.
*/
char	*create_random_str(size_t len)
{
	int		urandom;
	char	*random_str;

	random_str = ft_calloc((len + 1), sizeof(char));
	random_str[0] = '\0';
	urandom = open("/dev/urandom", O_RDONLY);
	if (urandom < 0)
		return (NULL);
	while (!random_str[0] || !ft_str_is_alnum(random_str)
		|| ft_strlen(random_str) != len)
		read(urandom, random_str, len);
	close(urandom);
	return (random_str);
}
