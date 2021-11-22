/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:42:11 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/22 02:06:23 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static t_type	print(const char *format, t_type i, va_list args)
{
	i.i++;
	if (format[i.i] == '%')
		i.sum += ft_putcharf('%');
	if (format[i.i] == 'd' || format[i.i] == 'i')
		i = type_d(args, i);
	if (format[i.i] == 'u')
		i.sum += ft_putnbr_base(va_arg(args, \
					unsigned int), 1, "0123456789");
	if (format[i.i] == 's')
		i = type_s(args, i);
	if (format[i.i] == 'c')
		i = type_c(args, i);
	if (format[i.i] == 'x')
		i.sum += ft_putnbr_base(va_arg(args, \
					unsigned int), 1, "0123456789abcdef");
	if (format[i.i] == 'X')
		i.sum += ft_putnbr_base(va_arg(args, \
					unsigned int), 1, "0123456789ABCDEF");
	if (format[i.i] == 'p')
		i = type_p(args, i);
	return (i);
}

static int	check(const char *format, va_list args)
{
	t_type	i;

	i.i = 0;
	i.sum = 0;
	while (format[i.i] != '\0')
	{
		if (format[i.i] == '%')
			i = print(format, i, args);
		else
			i.sum += ft_putcharf(format[i.i]);
		i.i++;
	}
	return (i.sum);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			sum;

	sum = 0;
	va_start(args, format);
	sum = check(format, args);
	va_end(args);
	return (sum);
}
