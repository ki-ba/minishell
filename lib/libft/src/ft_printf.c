/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:30:29 by kbarru            #+#    #+#             */
/*   Updated: 2025/01/29 16:05:23 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handle_unbr(unsigned long arg, char specifier)
{
	if (specifier == 'x')
		return (ft_put_ul_base((unsigned int)arg, HEX_BASE_LOWER, 0));
	else if (specifier == 'X')
		return (ft_put_ul_base((unsigned int)arg, HEX_BASE_UPPER, 0));
	else if (specifier == 'p')
	{
		ft_putstr_fd("0x", 1);
		return (2 + ft_put_ul_base(arg, HEX_BASE_LOWER, 0));
	}
	else if (specifier == 'c')
	{
		ft_putchar_fd((char)arg, 1);
		return (1);
	}
	else if (specifier == 'u')
		return (ft_put_ul_base((unsigned int)arg, DECIMAL_BASE, 0));
	else
		return (0);
}

static int	handle_integer_arg(va_list *args, char f_spec)
{
	if (ft_is_in(f_spec, SIGNED_FORMAT_SPECIFIERS))
		return (ft_putnbr_base(va_arg(*args, int), DECIMAL_BASE, 0));
	else if (f_spec == 'p')
		return (ft_handle_unbr((unsigned long)va_arg(*args, void *), f_spec));
	else if (ft_is_in(f_spec, UNSIGNED_FORMAT_SPECIFIERS))
		return (ft_handle_unbr(va_arg(*args, unsigned long), f_spec));
	else
	{
		ft_putchar_fd(va_arg(*args, int), 1);
		return (1);
	}
	return (0);
}

static int	ft_put_str_arg(char *arg)
{
	if (!arg)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(arg, 1);
	return (ft_strlen(arg));
}

static int	handle_argument(va_list *args, char specifier)
{
	if (ft_is_in(specifier, NUMERICAL_FORMAT_SPECIFIERS))
		return (handle_integer_arg(args, specifier));
	else if (ft_is_in(specifier, "s"))
		return (ft_put_str_arg(va_arg(*args, char *)));
	else if (ft_is_in(specifier, "c"))
		return (ft_putchar(va_arg(*args, int)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		fs;

	fs = 0;
	count = 0;
	va_start(args, format);
	while (*format)
	{
		fs = (*format == '%');
		format += fs;
		if (fs && ft_is_in(*(format), FTPRINTF_FORMAT_SPECIFIERS))
		{
			count += handle_argument(&args, *format);
			fs = 0;
		}
		else
			count += ft_putchar(*format);
		++format;
		va_end(args);
	}
	va_end(args);
	return (count);
}
