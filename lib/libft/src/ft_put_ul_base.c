/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_ul_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:06:34 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/07 21:33:37 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_ul_base(unsigned long nbr, char *base, int size)
{
	size_t	n;
	int		return_value;

	if (!base)
		return (0);
	n = ft_strlen(base);
	if (nbr < n)
	{
		ft_putchar_fd(base[nbr], 1);
		return (size + 1);
	}
	else
	{
		return_value = ft_put_ul_base(nbr / n, base, size + 1);
		ft_putchar_fd(base[nbr % n], 1);
		return (return_value);
	}
}
