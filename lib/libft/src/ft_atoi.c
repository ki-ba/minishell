/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:27:11 by kbarru            #+#    #+#             */
/*   Updated: 2025/04/16 10:46:15 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// First, any number of whitespaces
// Then, a single - or + char
// then numbers
// returns the current number on error.

static int	ft_issign(char c)
{
	return (c == '-' || c == '+');
}

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	number;
	long	check;

	number = 0;
	sign = 1;
	while (ft_iswhitespace(*nptr))
		++nptr;
	if (ft_issign(*nptr))
	{
		if (*nptr == '-')
			sign *= (-1);
		++nptr;
	}
	while (ft_isdigit(*nptr))
	{
		check = number;
		number = (number * 10) + (*nptr - 48);
		if (number < check && sign == 1)
			return (-1);
		else if (number < check && sign == -1)
			return (0);
		++nptr;
	}
	return (sign * (int)number);
}

static size_t	get_index(char c, const char str[])
{
	size_t	i;

	i = 0;
	while (str[i] && c != str[i])
		++i;
	if (c != str[i])
		return (0);
	return (i);
}

int	ft_atoi_base(const char nptr[], const char base[])
{
	int			sign;
	size_t		base_len;
	long long	number;

	base_len = ft_strlen(base);
	number = 0;
	sign = 1;
	while (ft_iswhitespace(*nptr))
		++nptr;
	if (ft_issign(*nptr))
	{
		if (*nptr == '-')
			sign *= (-1);
		++nptr;
	}
	while (ft_is_in(*nptr, base))
	{
		number = (number * base_len) + get_index(*nptr, base);
		++nptr;
	}
	return (sign * (int)number);
}
