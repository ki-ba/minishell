/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:04:06 by kiba              #+#    #+#             */
/*   Updated: 2025/03/09 11:04:12 by kiba             ###   ########lyon.fr   */
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

	i = 0;
	string = malloc(sizeof(char));
	string[0] = '\0';
	va_start(lst, n);
	while (i < n)
	{
		heap_add_suffix(va_arg(lst, char *), &string);
		++i;
	}
	va_end(lst);
	return (string);
}
