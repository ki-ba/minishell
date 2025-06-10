/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_non_empty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 10:43:58 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/10 12:20:47 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	@brief returns whether `str` is non-null AND non-empty or not.
 *	@param str the string to check.
 *	@returns 1 if `str` is a valid string of length > 0.
 *	@returns 0 otherwise.
*/
t_bool	ft_str_is_non_empty(char str[])
{
	return (str && str[0]);
}
