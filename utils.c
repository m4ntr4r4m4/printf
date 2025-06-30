/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Utility routines: base conversion & padding            +:+  +:+           */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdlib.h>

char *utoa_base(unsigned long long num, const char *base)
{
    unsigned long long tmp = num;
    int base_len = ft_strlen((char *)base);
    int len = 1;
    while (tmp >= (unsigned long long)base_len)
    {
        tmp /= base_len;
        len++;
    }
    char *str = malloc(len + 1);
    if (!str)
        return NULL;
    str[len] = '\0';
    while (len--)
    {
        str[len] = base[num % base_len];
        num /= base_len;
    }
    return str;
}

int put_chars(char c, int count)
{
    int sum = 0;
    while (count-- > 0)
        sum += ft_putcharf(c);
    return sum;
}
