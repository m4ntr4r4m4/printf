/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:40:21 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/22 01:59:02 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct t_type{
	int	i;
	int	sum;
}	t_type;
int		ft_printf(const char *format, ...);
int		ft_putnbr_base(unsigned long long num, int fd, char *base);
int		ft_putstrf(char *s);
int		ft_putcharf(char c);
t_type	type_p(va_list, t_type i);
t_type	type_c(va_list, t_type i);
t_type	type_s(va_list, t_type i);
t_type	type_x(va_list, t_type i);
t_type	type_X(va_list, t_type i);
t_type	type_d(va_list, t_type i);
t_type	type_u(va_list, t_type i);
#endif
