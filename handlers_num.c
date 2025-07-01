/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m4ntr4 <m4ntr4@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by m4ntr4            #+#    #+#             */
/*   Updated: 2025/07/01 04:46:46 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	print_signed(t_format *f, char *str, int ppad, int spad)
{
	int	sum;
	int	i;

	sum = 0;
	if (f->flags_minus)
	{
		if (f->sign)
			sum += ft_putcharf(f->sign);
		sum += put_chars('0', ppad);
		i = 0;
		while (i < (int)ft_strlen(str))
			sum += ft_putcharf(str[i++]);
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
			sum += ft_putcharf(str[i++]);
	}
	return (sum);
}

int	handle_int(t_format *f, int n)
{
	unsigned int	un;
	t_ptr			t;

	t.n = n;
	if (n < 0)
	{
		un = (unsigned int)(-(long)n);
		f->sign = '-';
	}
	else
	{
		un = (unsigned int)n;
		f->sign = (f->flags_plus) ? '+' : (f->flags_space ? ' ' : 0);
	}
	if (f->precision == 0 && t.n == 0)
		t.str = ft_strdup("");
	else if (n < 0)
		t.str = utoa_base(un, "0123456789");
	else
		t.str = ft_itoa((int)un);
	if (t.str == NULL)
		return (0);
	t.len = ft_strlen(t.str);
	if (f->precision >= 0)
		t.ppad = (f->precision > t.len) ? f->precision - t.len : 0;
	else if (f->flags_zero && !f->flags_minus)
		t.ppad = f->width - (f->sign ? 1 : 0) - t.len;
	else
		t.ppad = 0;
	if (t.ppad < 0)
		t.ppad = 0;
	t.spad = f->width - (f->sign ? 1 : 0) - t.ppad - t.len;
	if (t.spad < 0)
		t.spad = 0;
	t.sum = print_signed(f, t.str, t.ppad, t.spad);
	free(t.str);
	return (t.sum);
}

static int	print_unsigned(t_format *f, t_ptr t)
{
	int	i;

	t.sum = 0;
	if (f->flags_minus)
	{
		t.sum += put_chars('0', t.ppad);
		i = 0;
		while (i < (int)ft_strlen(t.str))
			t.sum += ft_putcharf(t.str[i++]);
		t.sum += put_chars(' ', t.spad);
	}
	else
	{
		t.sum += put_chars(' ', t.spad);
		t.sum += put_chars('0', t.ppad);
		i = 0;
		while (i < (int)ft_strlen(t.str))
			t.sum += ft_putcharf(t.str[i++]);
	}
	return (t.sum);
}

int	handle_uint(t_format *f, unsigned int n)
{
	t_ptr	t;

	t.n = n;
	if (f->precision == 0 && t.n == 0)
		t.str = ft_strdup("");
	else
		t.str = utoa_base(t.n, "0123456789");
	if (t.str == NULL)
		return (0);
	t.len = ft_strlen(t.str);
	if (f->precision >= 0)
		t.ppad = (f->precision > t.len) ? f->precision - t.len : 0;
	else if (f->flags_zero && !f->flags_minus)
		t.ppad = f->width - t.len;
	else
		t.ppad = 0;
	if (t.ppad < 0)
		t.ppad = 0;
	t.spad = f->width - t.ppad - t.len;
	if (t.spad < 0)
		t.spad = 0;
	t.sum = print_unsigned(f, t);
	free(t.str);
	return (t.sum);
}
