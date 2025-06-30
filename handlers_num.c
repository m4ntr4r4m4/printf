/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Integer and unsigned handlers for bonus           +:+  +:+           */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdlib.h>

static int print_signed(t_format *f, char *str, char sign, int ppad, int spad)
{
    int sum = 0;
    if (f->flags_minus)
    {
        if (sign)
            sum += ft_putcharf(sign);
        sum += put_chars('0', ppad);
        for (int i = 0; i < (int)ft_strlen(str); i++)
            sum += ft_putcharf(str[i]);
        sum += put_chars(' ', spad);
    }
    else
    {
        sum += put_chars(' ', spad);
        if (sign)
            sum += ft_putcharf(sign);
        sum += put_chars('0', ppad);
        for (int i = 0; i < (int)ft_strlen(str); i++)
            sum += ft_putcharf(str[i]);
    }
    return sum;
}

int handle_int(t_format *f, int n)
{
    unsigned int un;
    char sign = 0;
    char *str;
    int len, ppad, spad;

    if (n < 0)
        un = -(long)n, sign = '-';
    else
        un = n, sign = (f->flags_plus ? '+' : (f->flags_space ? ' ' : 0));
    if (f->precision == 0 && n == 0)
        str = ft_strdup("");
    else
        str = ft_itoa(un);
    if (!str)
        return 0;
    len = ft_strlen(str);
    if (f->precision >= 0)
        ppad = f->precision > len ? f->precision - len : 0;
    else if (f->flags_zero && !f->flags_minus)
        ppad = f->width - (sign ? 1 : 0) - len;
    else
        ppad = 0;
    if (ppad < 0)
        ppad = 0;
    spad = f->width - (sign ? 1 : 0) - ppad - len;
    if (spad < 0)
        spad = 0;
    int sum = print_signed(f, str, sign, ppad, spad);
    free(str);
    return sum;
}

static int print_unsigned(t_format *f, char *str, int ppad, int spad)
{
    int sum = 0;
    if (f->flags_minus)
    {
        sum += put_chars('0', ppad);
        for (int i = 0; i < (int)ft_strlen(str); i++)
            sum += ft_putcharf(str[i]);
        sum += put_chars(' ', spad);
    }
    else
    {
        sum += put_chars(' ', spad);
        sum += put_chars('0', ppad);
        for (int i = 0; i < (int)ft_strlen(str); i++)
            sum += ft_putcharf(str[i]);
    }
    return sum;
}

int handle_uint(t_format *f, unsigned int n)
{
    char *str;
    int len, ppad, spad;

    if (f->precision == 0 && n == 0)
        str = ft_strdup("");
    else
        str = utoa_base(n, "0123456789");
    if (!str)
        return 0;
    len = ft_strlen(str);
    if (f->precision >= 0)
        ppad = f->precision > len ? f->precision - len : 0;
    else if (f->flags_zero && !f->flags_minus)
        ppad = f->width - len;
    else
        ppad = 0;
    if (ppad < 0)
        ppad = 0;
    spad = f->width - ppad - len;
    if (spad < 0)
        spad = 0;
    int sum = print_unsigned(f, str, ppad, spad);
    free(str);
    return sum;
}
