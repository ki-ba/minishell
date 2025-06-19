/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:53:28 by mlouis            #+#    #+#             */
/*   Updated: 2025/06/10 14:04:13 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	a_lst;
	int		len;
	int		res;

	if (!format)
		return (-1);
	va_start(a_lst, format);
	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			res = converter_handler_fd(*format, a_lst, fd);
			if (res == -1)
				return (-1);
			len += res;
			format++;
			continue ;
		}
		len = len + ft_putchar_fd(*format, fd);
		format++;
	}
	va_end(a_lst);
	return (len);
}
