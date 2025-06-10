/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 10:32:58 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/09 11:16:47 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	@brief prints the values of the array of strings passed as parameter.
 *	@param arr the array to print.
*/
void	ft_print_arr(char **arr)
{
	int	i;

	ft_printf("\n\n === ARRAY PRINTING ===\n\n");
	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		ft_printf("%s\n", arr[i]);
	ft_printf("\n\n ==========\n\n");
}
