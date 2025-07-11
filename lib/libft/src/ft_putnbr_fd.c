/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:11:07 by kbarru            #+#    #+#             */
/*   Updated: 2025/06/10 13:53:08 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int nb, int fd)
{
	int		len;
	char	cnb;

	len = 0;
	if (nb == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (nb < 0)
	{
		nb = -nb;
		len = len + ft_putchar_fd('-', fd);
	}
	cnb = nb % 10 + '0';
	if (nb > 9)
		len = len + ft_putnbr_fd(nb / 10, fd);
	return (len + ft_putchar_fd(cnb, fd));
}
