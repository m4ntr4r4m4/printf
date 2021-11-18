/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:42:11 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/18 18:09:18 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	print(const char *format, int i, va_list args)
{
	if (format[i] == '%')
		i++;
	if (format[i] == '%')
		ft_putchar_fd('%', 1);
	if (format[i] == 'd')
		ft_putnbr_fd(va_arg(args, int), 1);
	if (format[i] == 's')
		ft_putstr_fd(va_arg(args, char *), 1);
	if (format[i] == 'c')
		ft_putchar_fd(va_arg(args, int), 1);
	if (format[i] == 'u')
		ft_putnbr_fd(va_arg(args, unsigned int), 1);
	if (format[i] == 'x')
		ft_putnbr_16(va_arg(args, unsigned int));
	if (format[i] == 'p')
	{
		ft_putstr_fd("0x", 1);
		ft_putnbr_16((va_arg(args, unsigned int)));
	}
	return (i);
}

static int	check(const char *format, va_list args)
{
	int	i;

	i = 0;
	while (format[i] != '\0')
	{
		i = print(format, i, args);
		i++;
		if (format[i] != '%')
			ft_putchar_fd(format[i], 1);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			sum;

	sum = 0;
	va_start(args, format);
	sum = check(format, args);
	va_end(args);
	return (0);
}
