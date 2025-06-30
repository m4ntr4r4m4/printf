/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_char_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Character and string handlers for bonus            +:+  +:+           */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int handle_char(t_format *f, char c)
{
    int sum = 0;
    int pad = f->width > 1 ? f->width - 1 : 0;
    if (f->flags_minus)
    {
        sum += ft_putcharf(c);
        sum += put_chars(' ', pad);
    }
    else
    {
        char fill = f->flags_zero ? '0' : ' ';
        sum += put_chars(fill, pad);
        sum += ft_putcharf(c);
    }
    return sum;
}

int handle_str(t_format *f, char *s)
{
    int sum = 0;
    if (!s)
        s = "(null)";
    int len = ft_strlen(s);
    if (f->precision >= 0 && f->precision < len)
        len = f->precision;
    if (f->flags_minus)
    {
        for (int i = 0; i < len; i++)
            sum += ft_putcharf(s[i]);
        sum += put_chars(' ', f->width - len);
    }
    else
    {
        sum += put_chars(' ', f->width - len);
        for (int i = 0; i < len; i++)
            sum += ft_putcharf(s[i]);
    }
    return sum;
}
