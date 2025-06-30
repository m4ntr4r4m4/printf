/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Bonus flags and width/precision parsing             +:+  +:+           */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void init_format(t_format *f)
{
    f->flags_minus = 0;
    f->flags_zero = 0;
    f->flags_hash = 0;
    f->flags_space = 0;
    f->flags_plus = 0;
    f->width = 0;
    f->precision = -1;
    f->specifier = 0;
}

void parse_format(const char *fmt, int *i, t_format *f)
{
    init_format(f);
    (*i)++;
    while (fmt[*i] == '-' || fmt[*i] == '0' || fmt[*i] == '#' ||
           fmt[*i] == ' ' || fmt[*i] == '+')
    {
        if (fmt[*i] == '-')
            f->flags_minus = 1;
        else if (fmt[*i] == '0')
            f->flags_zero = 1;
        else if (fmt[*i] == '#')
            f->flags_hash = 1;
        else if (fmt[*i] == ' ')
            f->flags_space = 1;
        else if (fmt[*i] == '+')
            f->flags_plus = 1;
        (*i)++;
    }
    if (fmt[*i] >= '0' && fmt[*i] <= '9')
    {
        f->width = 0;
        while (fmt[*i] >= '0' && fmt[*i] <= '9')
            f->width = f->width * 10 + (fmt[(*i)++] - '0');
    }
    if (fmt[*i] == '.')
    {
        (*i)++;
        f->precision = 0;
        while (fmt[*i] >= '0' && fmt[*i] <= '9')
            f->precision = f->precision * 10 + (fmt[(*i)++] - '0');
    }
    f->specifier = fmt[*i];
}
