/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:30:48 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/09 11:14:23 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int n)
{
	if (n < 0 && n != -2147483648)
		return (-n);
	else if (n < 0)
		return (0);
	return (n);
}

static int	get_n_size(int n)
{
	int	i;

	i = 0;
	while (n / 10)
	{
		++i;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	int		is_neg;
	char	*number;

	is_neg = 0;
	len = 1;
	if (n < 0)
		is_neg = 1;
	len += get_n_size(n);
	number = malloc((len + is_neg + 1) * sizeof(char));
	if (!number)
		return (0);
	if (is_neg)
		number[0] = '-';
	number[len + is_neg] = '\0';
	while ((len--))
	{
		number[(len) + is_neg] = (ft_abs(n % 10)) + 48;
		n /= 10;
	}
	return (number);
}
