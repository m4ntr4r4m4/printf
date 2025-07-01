/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m4ntr4 <m4ntr4@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by m4ntr4            #+#    #+#             */
/*   Updated: 2025/07/01 00:00:00 by m4ntr4            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	print_signed(t_format *f, char *str, int ppad, int spad)
{
   int sum;
   int i;

   sum = 0;
   if (f->flags_minus)
   {
       if (f->sign)
           sum += ft_putcharf(f->sign);
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
       if (f->sign)
           sum += ft_putcharf(f->sign);
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

int	handle_int(t_format *f, int n)
{
   unsigned int un;
   char *str;
   int len;
   int ppad;
   int spad;
   int sum;

   if (n < 0)
   {
       un = (unsigned int)(-(long)n);
       f->sign = '-';
   }
   else
   {
       un = (unsigned int)n;
       f->sign = (f->flags_plus) ? '+' :
                 (f->flags_space ? ' ' : 0);
   }
   if (f->precision == 0 && n == 0)
       str = ft_strdup("");
   else
       str = ft_itoa(un);
   if (str == NULL)
       return (0);
   len = ft_strlen(str);
   if (f->precision >= 0)
       ppad = (f->precision > len) ? f->precision - len : 0;
   else if (f->flags_zero && !f->flags_minus)
       ppad = f->width - (f->sign ? 1 : 0) - len;
   else
       ppad = 0;
   if (ppad < 0)
       ppad = 0;
   spad = f->width - (f->sign ? 1 : 0) - ppad - len;
   if (spad < 0)
       spad = 0;
   sum = print_signed(f, str, ppad, spad);
   free(str);
   return (sum);
}

static int	print_unsigned(t_format *f, char *str, int ppad, int spad)
{
   int sum;
   int i;

   sum = 0;
   if (f->flags_minus)
   {
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

int	handle_uint(t_format *f, unsigned int n)
{
   char *str;
   int len;
   int ppad;
   int spad;
   int sum;

   if (f->precision == 0 && n == 0)
       str = ft_strdup("");
   else
       str = utoa_base(n, "0123456789");
   if (str == NULL)
       return (0);
   len = ft_strlen(str);
   if (f->precision >= 0)
       ppad = (f->precision > len) ? f->precision - len : 0;
   else if (f->flags_zero && !f->flags_minus)
       ppad = f->width - len;
   else
       ppad = 0;
   if (ppad < 0)
       ppad = 0;
   spad = f->width - ppad - len;
   if (spad < 0)
       spad = 0;
   sum = print_unsigned(f, str, ppad, spad);
   free(str);
   return (sum);
}
