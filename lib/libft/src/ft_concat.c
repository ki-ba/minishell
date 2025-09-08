/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kiba@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:04:06 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/03 10:00:19 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	@brief concatenates the first `n` strings passed as parameters.
*	@brief the resulting string is allocated on the heap.
*	@param n the number of strings to concatenate.
*	@param ... the strings to concatenate.
*	@returns the resulting concatenated string.
*	@note passed strings do not need to be allocated on the heap.
*	@note no freeing of said strings is done.
*/
char	*ft_concat(size_t n, ...)
{
	va_list	lst;
	size_t	i;
	char	*string;
	int		err;

	i = 0;
	string = ft_calloc(1, sizeof(char));
	if (!string)
		return (NULL);
	va_start(lst, n);
	while (i < n)
	{
		err = heap_add_suffix(va_arg(lst, char *), &string);
		if (err)
		{
			free(string);
			va_end(lst);
			return (NULL);
		}
		++i;
	}
	va_end(lst);
	return (string);
}
