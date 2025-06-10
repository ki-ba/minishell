/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_arr_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 10:56:24 by kiba              #+#    #+#             */
/*   Updated: 2025/03/09 11:02:46 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	@brief frees the array of strings passed as parameter.
	@param arr the array to free.
*/
void	ft_free_arr(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr && arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free(arr);
}

/*
 *	@brief returns the length of specified null-terminated array.
 *	@brief the null terminator is not counted.
*/
int	get_arr_length(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		++i;
	return (i);
}

/*
 *	@brief allocates a copy of the array of strings passed as a parameter.
 *	@param arr the array to duplicate.
*/
char	**duplicate_arr(char **arr)
{
	int		i;
	int		size;
	char	**dup;

	i = -1;
	if (!arr)
		return (NULL);
	size = get_arr_length(arr);
	dup = malloc(sizeof(char *) * (size + 1));
	while (++i < size)
		dup[i] = ft_strdup(arr[i]);
	dup[i] = 0;
	return (dup);
}

/*
	@brief adds a suffix to each string of specified array in place.
	@param prefix the suffix to add.
	@param s2 the string to add a suffix to.
*/
void	str_arr_suffix(char **arr, char *suffix)
{
	int	i;

	i = -1;
	while (arr && arr[++i] && suffix)
		heap_add_suffix(suffix, &(arr[i]));
}
