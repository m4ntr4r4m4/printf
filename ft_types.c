/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:35:05 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/22 01:57:00 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
typedef struct t_type
{
    int i;
    int sum;
} t_type;

t_type	type_d(va_list args, t_type i)
{
	long	num;
	char	*str;

	num = va_arg(args, int);
	ft_putnbr_fd(num, 1);
	i.sum += ft_strlen(str = ft_itoa(num));
	free(str);
	return (i);
}

t_type	type_p(va_list args, t_type i)
{
	ft_putstr_fd("0x", 1);
	i.sum += ft_putnbr_base(va_arg(args, \
				unsigned long), 1, "0123456789abcdef") + 2;
	return (i);
}

t_type	type_c(va_list args, t_type i)
{
	i.sum += ft_putcharf(va_arg(args, int));
	return (i);
}

t_type	type_s(va_list args, t_type i)
{
	i.sum += ft_putstrf(va_arg(args, char *));
	return (i);
}
