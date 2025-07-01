/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m4ntr4 <m4ntr4@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by m4ntr4            #+#    #+#             */
/*   Updated: 2025/07/01 00:00:00 by m4ntr4            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	handle_format(t_format *f, va_list args)
{
   if (f->specifier == 'c')
       return (handle_char(f, va_arg(args, int)));
   if (f->specifier == 's')
       return (handle_str(f, va_arg(args, char *)));
   if (f->specifier == 'p')
       return (handle_ptr(f, va_arg(args, void *)));
   if (f->specifier == 'd' || f->specifier == 'i')
       return (handle_int(f, va_arg(args, int)));
   if (f->specifier == 'u')
       return (handle_uint(f, va_arg(args, unsigned int)));
   if (f->specifier == 'x')
       return (handle_hex(f, va_arg(args, unsigned int),
               "0123456789abcdef", 'x'));
   if (f->specifier == 'X')
       return (handle_hex(f, va_arg(args, unsigned int),
               "0123456789ABCDEF", 'X'));
   if (f->specifier == '%')
       return (handle_char(f, '%'));
   return (0);
}

int	ft_printf(const char *format, ...)
{
   va_list args;
   int     sum;
   int     i;
   t_format f;

   sum = 0;
   i = 0;
   va_start(args, format);
   while (format[i] != '\0')
   {
       if (format[i] == '%')
       {
           parse_format(format, &i, &f);
           sum += handle_format(&f, args);
           i++;
       }
       else
           sum += ft_putcharf(format[i++]);
   }
   va_end(args);
   return (sum);
}
