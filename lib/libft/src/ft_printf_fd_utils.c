/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:57:21 by mlouis            #+#    #+#             */
/*   Updated: 2025/06/10 14:10:22 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	output_char_fd(char c_arg, int fd);
static int	output_str_fd(va_list a_lst, int fd);
static int	output_hex_fd(const char format, va_list a_lst, int fd);
static int	output_ptr_fd(va_list a_lst, int fd);

int	converter_handler_fd(const char format, va_list a_lst, int fd)
{
	if (format == '\0')
		return (-1);
	if (format == '%')
		return (ft_putchar_fd(format, fd));
	if (format == 'c')
		return (output_char_fd((char) va_arg(a_lst, int), fd));
	if (format == 's')
		return (output_str_fd(a_lst, fd));
	if (format == 'd' || format == 'i')
		return (ft_putnbr_fd(va_arg(a_lst, int), fd));
	if (format == 'u')
		return (ft_putnbr_positive_fd(va_arg(a_lst, unsigned int), fd));
	if (format == 'x' || format == 'X')
		return (output_hex_fd(format, a_lst, fd));
	if (format == 'p')
		return (output_ptr_fd(a_lst, fd));
	return (ft_putchar_fd('%', 1) + output_char_fd(format, fd));
}

static int	output_char_fd(char c_arg, int fd)
{
	int		len;

	if (c_arg != 0)
		len = ft_putchar_fd(c_arg, fd);
	else
		len = write(fd, "\0", 1);
	return (len);
}

static int	output_str_fd(va_list a_lst, int fd)
{
	int		len;
	char	*s_arg;

	s_arg = ft_strdup((char *) va_arg(a_lst, char *));
	if (s_arg)
	{
		len = ft_putstr_fd(s_arg, fd);
		free(s_arg);
	}
	else
		len = ft_putstr_fd("(null)", fd);
	return (len);
}

static int	output_hex_fd(const char format, va_list a_lst, int fd)
{
	int				len;
	int				n_arg;
	unsigned long	ul_arg;
	char			base[17];

	n_arg = va_arg(a_lst, int);
	if (format == 'x')
		ft_strlcpy(base, HEX_BASE_LOWER, 17);
	else
		ft_strlcpy(base, HEX_BASE_UPPER, 17);
	if (n_arg >= 0)
		len = ft_putnbr_base_fd(n_arg, base, fd);
	else
	{
		ul_arg = LONG_OVERFLOW + n_arg;
		len = ft_putnbr_base_fd(ul_arg, base, fd);
	}
	return (len);
}

static int	output_ptr_fd(va_list a_lst, int fd)
{
	int				len;
	unsigned long	ul_arg;

	ul_arg = va_arg(a_lst, unsigned long);
	if (ul_arg != 0)
	{
		len = ft_putstr_fd("0x", fd);
		len += ft_putnbr_base_fd(ul_arg, HEX_BASE_LOWER, fd);
	}
	else
		len = ft_putstr_fd("(nil)", fd);
	return (len);
}
