/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_hex_ptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Hexadecimal and pointer handlers for bonus        +:+  +:+           */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdlib.h>

static int print_hex(t_format *f, char *str, int prefix_len, int ppad, int spad, char prefix)
{
    int sum = 0;
    if (f->flags_minus)
    {
        if (prefix_len)
            sum += ft_putcharf('0'), sum += ft_putcharf(prefix);
        sum += put_chars('0', ppad);
        for (int i = 0; i < (int)ft_strlen(str); i++)
            sum += ft_putcharf(str[i]);
        sum += put_chars(' ', spad);
    }
    else
    {
        sum += put_chars(' ', spad);
        if (prefix_len)
            sum += ft_putcharf('0'), sum += ft_putcharf(prefix);
        sum += put_chars('0', ppad);
        for (int i = 0; i < (int)ft_strlen(str); i++)
            sum += ft_putcharf(str[i]);
    }
    return sum;
}

int handle_hex(t_format *f, unsigned int n, const char *base, char prefix)
{
    char *str;
    int len, ppad, spad, prefix_len;

    prefix_len = (f->flags_hash && n) ? 2 : 0;
    if (f->precision == 0 && n == 0)
        str = ft_strdup("");
    else
        str = utoa_base(n, base);
    if (!str)
        return 0;
    len = ft_strlen(str);
    if (f->precision >= 0)
        ppad = f->precision > len ? f->precision - len : 0;
    else if (f->flags_zero && !f->flags_minus)
        ppad = f->width - prefix_len - len;
    else
        ppad = 0;
    if (ppad < 0)
        ppad = 0;
    spad = f->width - prefix_len - ppad - len;
    if (spad < 0)
        spad = 0;
    int sum = print_hex(f, str, prefix_len, ppad, spad, prefix);
    free(str);
    return sum;
}

static int print_ptr(t_format *f, char *str, int ppad, int spad)
{
    int sum = 0;
    if (f->flags_minus)
    {
        sum += ft_putcharf('0'), sum += ft_putcharf('x');
        sum += put_chars('0', ppad);
        for (int i = 0; i < (int)ft_strlen(str); i++)
            sum += ft_putcharf(str[i]);
        sum += put_chars(' ', spad);
    }
    else
    {
        sum += put_chars(' ', spad);
        sum += ft_putcharf('0'), sum += ft_putcharf('x');
        sum += put_chars('0', ppad);
        for (int i = 0; i < (int)ft_strlen(str); i++)
            sum += ft_putcharf(str[i]);
    }
    return sum;
}

int handle_ptr(t_format *f, void *p)
{
    unsigned long n = (unsigned long)p;
    char *str;
    int len, ppad, spad;

    str = utoa_base(n, "0123456789abcdef");
    if (!str)
        return 0;
    len = ft_strlen(str);
    if (f->precision >= 0)
        ppad = f->precision > len ? f->precision - len : 0;
    else
        ppad = 0;
    spad = f->width - 2 - ppad - len;
    if (spad < 0)
        spad = 0;
    int sum = print_ptr(f, str, ppad, spad);
    free(str);
    return sum;
}
