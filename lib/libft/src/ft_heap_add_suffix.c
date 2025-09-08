/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap_add_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:05:01 by kiba              #+#    #+#             */
/*   Updated: 2025/03/09 11:05:12 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
*	@brief adds specified suffix to a `s1` in place-ish.
*	@brief copies s1, adds the suffix, then frees the previous `s1`
*	@brief and replaces it by the new
*	@param s1 pointer to the current string.
*	@param suffix the suffix to add.
*	@note will cause a segfault if s1 was not allocated on the heap.
*/
int	heap_add_suffix(const char *suffix, char **s1)
{
	size_t	suffix_len;
	size_t	s1_len;
	char	*s1_dup;
	size_t	size;

	if (!s1 || !suffix)
		return (1);
	s1_dup = ft_strdup(*s1);
	if (!s1_dup)
		return (1);
	suffix_len = ft_strlen(suffix);
	s1_len = ft_strlen(s1_dup);
	free(*s1);
	size = (s1_len + suffix_len + 1) * sizeof(char);
	*s1 = malloc(size);
	if ((*s1))
	{
		ft_strlcpy(*s1, s1_dup, size);
		ft_strlcat(*s1, suffix, size);
	}
	free(s1_dup);
	return ((*s1) == NULL);
}
