/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Updated for bonus implementation                           :+:      :+:    :+:   */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./includes/libft.h"
# include <stdarg.h>

typedef struct s_format
{
    int flags_minus;
    int flags_zero;
    int flags_hash;
    int flags_space;
    int flags_plus;
    int width;
    int precision;
    char specifier;
} t_format;

int ft_printf(const char *format, ...);
int ft_putcharf(char c);
int ft_putstrf(char *s);
int ft_putnbr_base(unsigned long long num, int fd, char *base);

#endif
