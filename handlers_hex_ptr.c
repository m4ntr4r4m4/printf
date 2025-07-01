/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_hex_ptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m4ntr4 <m4ntr4@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by m4ntr4            #+#    #+#             */
/*   Updated: 2025/07/01 04:12:54 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	print_hex(t_format *f, t_ptr ptr)
{
	int		prefix_len;
	char	prefix;

	ptr.sum = 0;
	if (f->flags_hash && ptr.n != 0)
		prefix_len = 2;
	else
		prefix_len = 0;
	prefix = f->specifier;
	if (f->flags_minus)
		ptr.sum += ft_sum(ptr, prefix_len, prefix);
	else
		ptr.sum += ft_sum2(ptr, prefix_len, prefix);
	return (ptr.sum);
}

int	ft_ppad(t_format *f, t_ptr *ptr)
{
	if (f->precision >= 0)
	{
		if (f->precision > ptr->len)
			ptr->ppad = f->precision - ptr->len;
		else
			ptr->ppad = 0;
	}
	else if (f->flags_zero && !f->flags_minus)
		ptr->ppad = f->width - (f->flags_hash && ptr->n ? 2 : 0) - ptr->len;
	else
		ptr->ppad = 0;
	if (ptr->ppad < 0)
		ptr->ppad = 0;
	if (f->flags_hash && ptr->n)
		ptr->spad = f->width - 2 - ptr->ppad - ptr->len;
	else
		ptr->spad = f->width - ptr->ppad - ptr->len;
	if (ptr->spad < 0)
		ptr->spad = 0;
	return (ptr->ppad);
}

int	handle_hex(t_format *f, unsigned int n, const char *base, char pre)
{
	t_ptr ptr;

	(void)pre;
	ptr.n = n;
	if (f->precision == 0 && ptr.n == 0)
		ptr.str = ft_strdup("");
	else
		ptr.str = utoa_base(ptr.n, (char *)base);
	if (ptr.str == NULL)
		return (0);
	ptr.len = ft_strlen(ptr.str);
		ptr.ppad = ft_ppad(f, &ptr);
	ptr.sum = print_hex(f, ptr);
	free(ptr.str);
	return (ptr.sum);
}

static int	print_ptr(t_format *f, char *str, int ppad, int spad)
{
	int	sum;
	int	i;

	sum = 0;
	if (f->flags_minus)
	{
		sum += ft_putcharf('0');
		sum += ft_putcharf('x');
		sum += put_chars('0', ppad);
		i = 0;
		while (i < (int)ft_strlen(str))
			sum += ft_putcharf(str[i++]);
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
			sum += ft_putcharf(str[i++]);
	}
	return (sum);
}

int	handle_ptr(t_format *f, void *p)
{
	t_ptr	t;

	/* Handle null pointer in same way as standard printf ("(nil)") */
	if (p == NULL && f->precision < 0)
		return (ft_putstrf("(nil)"));
	t.n = (unsigned long)p;
	t.str = utoa_base(t.n, "0123456789abcdef");
	if (t.str == NULL)
		return (0);
	t.len = ft_strlen(t.str);
	if (f->precision >= 0)
	{
		if (f->precision > t.len)
			t.ppad = f->precision - t.len;
		else
			t.ppad = 0;
	}
	else
		t.ppad = 0;
	if (f->width - 2 - t.ppad - t.len < 0)
		t.spad = 0;
	else
		t.spad = f->width - 2 - t.ppad - t.len;
	t.sum = print_ptr(f, t.str, t.ppad, t.spad);
	free(t.str);
	return (t.sum);
}
