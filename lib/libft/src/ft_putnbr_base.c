/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:05:46 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/07 21:33:14 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(int nbr, char *base, int size)
{
	int		n;
	long	lnbr;
	int		return_value;

	if (!base)
		return (0);
	lnbr = nbr;
	n = ft_strlen(base);
	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		lnbr *= (-1);
		++size;
	}
	if (lnbr < n)
	{
		ft_putchar_fd(base[lnbr], 1);
		return (size + 1);
	}
	else
	{
		return_value = ft_putnbr_base(lnbr / n, base, size + 1);
		ft_putchar_fd(base[lnbr % n], 1);
		return (return_value);
	}
}
