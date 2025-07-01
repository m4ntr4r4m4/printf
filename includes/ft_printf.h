/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m4ntr4 <m4ntr4@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by m4ntr4            #+#    #+#             */
/*   Updated: 2025/07/01 00:00:00 by m4ntr4            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
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
    char sign;
} t_format;

int ft_printf(const char *format, ...);
int ft_putcharf(int c);
int ft_putstrf(char *s);
int ft_putnbr_base(unsigned long long num, int fd, char *base);
char *utoa_base(unsigned long long num, const char *base);
int put_chars(char c, int count);
void parse_format(const char *fmt, int *i, t_format *f);
int handle_char(t_format *f, char c);
int handle_str(t_format *f, char *s);
int handle_int(t_format *f, int n);
int handle_uint(t_format *f, unsigned int n);
int handle_hex(t_format *f, unsigned int n, const char *base, char prefix);
int handle_ptr(t_format *f, void *p);

#endif
