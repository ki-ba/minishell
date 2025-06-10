/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multifree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 10:53:30 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/09 11:13:21 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

/*
*	@brief frees `n_simple` variables and `n_arr` arrays of strings.
*	@param n_simple the number of simple variables to free.
*	@param n_arr the number of arrays of strings to free.
*	@param ... `n_simple` variables followed by `n_arr` arrays.
*		If more arguments are provided,
*	they will not be freed.
*/
void	ft_multifree(int n_simple, int n_arr, ...)
{
	int		i;
	va_list	args;
	char	*current_var;
	char	**current_array;

	va_start(args, n_arr);
	i = 0;
	while (i < n_simple)
	{
		current_var = va_arg(args, char *);
		free(current_var);
		++i;
	}
	while (i < n_arr - n_simple)
	{
		current_array = va_arg(args, char **);
		ft_free_arr(current_array);
		++i;
	}
	va_end(args);
}
