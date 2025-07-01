/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_hex_ptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m4ntr4 <m4ntr4@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by m4ntr4            #+#    #+#             */
/*   Updated: 2025/07/01 00:00:00 by m4ntr4            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	print_hex(t_format *f, char *str, int ppad, int spad)
{
   int sum;
   int i;
   int prefix_len;
   char prefix;

   sum = 0;
   prefix_len = (f->flags_hash && *str) ? 2 : 0;
   prefix = f->specifier;
   if (f->flags_minus)
   {
       if (prefix_len)
       {
           sum += ft_putcharf('0');
           sum += ft_putcharf(prefix);
       }
       sum += put_chars('0', ppad);
       i = 0;
       while (i < (int)ft_strlen(str))
       {
           sum += ft_putcharf(str[i]);
           i++;
       }
       sum += put_chars(' ', spad);
   }
   else
   {
       sum += put_chars(' ', spad);
       if (prefix_len)
       {
           sum += ft_putcharf('0');
           sum += ft_putcharf(prefix);
       }
       sum += put_chars('0', ppad);
       i = 0;
       while (i < (int)ft_strlen(str))
       {
           sum += ft_putcharf(str[i]);
           i++;
       }
   }
   return (sum);
}

int	handle_hex(t_format *f, unsigned int n, const char *base, char pre)
{
   char *str;
   int len;
   int ppad;
   int spad;
   int sum;

   (void)pre;
   if (f->precision == 0 && n == 0)
       str = ft_strdup("");
   else
       str = utoa_base(n, (char *)base);
   if (str == NULL)
       return (0);
   len = ft_strlen(str);
   if (f->precision >= 0)
       ppad = (f->precision > len) ? f->precision - len : 0;
   else if (f->flags_zero && !f->flags_minus)
       ppad = f->width - ((f->flags_hash && n) ? 2 : 0) - len;
   else
       ppad = 0;
   if (ppad < 0)
       ppad = 0;
   spad = f->width - ((f->flags_hash && n) ? 2 : 0) - ppad - len;
   if (spad < 0)
       spad = 0;
   sum = print_hex(f, str, ppad, spad);
   free(str);
   return (sum);
}

static int	print_ptr(t_format *f, char *str, int ppad, int spad)
{
   int sum;
   int i;

   sum = 0;
   if (f->flags_minus)
   {
       sum += ft_putcharf('0');
       sum += ft_putcharf('x');
       sum += put_chars('0', ppad);
       i = 0;
       while (i < (int)ft_strlen(str))
       {
           sum += ft_putcharf(str[i]);
           i++;
       }
       sum += put_chars(' ', spad);
   }
   else
   {
       sum += put_chars(' ', spad);
       sum += ft_putcharf('0');
       sum += ft_putcharf('x');
       sum += put_chars('0', ppad);
       i = 0;
       while (i < (int)ft_strlen(str))
       {
           sum += ft_putcharf(str[i]);
           i++;
       }
   }
   return (sum);
}

int	handle_ptr(t_format *f, void *p)
{
   unsigned long n;
   char *str;
   int len;
   int ppad;
   int spad;
   int sum;

   n = (unsigned long)p;
   str = utoa_base(n, "0123456789abcdef");
   if (str == NULL)
       return (0);
   len = ft_strlen(str);
   if (f->precision >= 0)
       ppad = (f->precision > len) ? f->precision - len : 0;
   else
       ppad = 0;
   if (f->width - 2 - ppad - len < 0)
       spad = 0;
   else
       spad = f->width - 2 - ppad - len;
   sum = print_ptr(f, str, ppad, spad);
   free(str);
   return (sum);
}
