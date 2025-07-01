/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_char_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m4ntr4 <m4ntr4@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by m4ntr4            #+#    #+#             */
/*   Updated: 2025/07/01 00:00:00 by m4ntr4            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_char(t_format *f, char c)
{
   int sum;
   int pad;
   char fill;

   sum = 0;
   pad = (f->width > 1) ? f->width - 1 : 0;
   if (f->flags_minus)
   {
       sum += ft_putcharf(c);
       sum += put_chars(' ', pad);
   }
   else
   {
       fill = (f->flags_zero) ? '0' : ' ';
       sum += put_chars(fill, pad);
       sum += ft_putcharf(c);
   }
   return (sum);
}

int	handle_str(t_format *f, char *s)
{
   int sum;
   int len;
   int i;

   sum = 0;
   if (s == NULL)
       s = "(null)";
   len = ft_strlen(s);
   if (f->precision >= 0 && f->precision < len)
       len = f->precision;
   if (f->flags_minus)
   {
       i = 0;
       while (i < len)
       {
           sum += ft_putcharf(s[i]);
           i++;
       }
       sum += put_chars(' ', f->width - len);
   }
   else
   {
       sum += put_chars(' ', f->width - len);
       i = 0;
       while (i < len)
       {
           sum += ft_putcharf(s[i]);
           i++;
       }
   }
   return (sum);
}
