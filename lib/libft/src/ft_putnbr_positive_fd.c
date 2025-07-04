/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_positive_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:01:38 by mlouis            #+#    #+#             */
/*   Updated: 2025/06/10 14:01:59 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_positive_fd(unsigned int n, int fd)
{
	char	cnb;
	int		len;

	cnb = n % 10 + '0';
	len = 0;
	if (n > 9)
		len = len + ft_putnbr_fd(n / 10, fd);
	len = len + ft_putchar_fd(cnb, fd);
	return (len);
}
