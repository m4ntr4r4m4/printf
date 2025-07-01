/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m4ntr4 <m4ntr4@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by m4ntr4            #+#    #+#             */
/*   Updated: 2025/07/01 00:00:00 by m4ntr4            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
	#include "ft_printf.h"

	static void	init_format(t_format *f)
	{
		f->flags_minus = 0;
		f->flags_zero = 0;
		f->flags_hash = 0;
		f->flags_space = 0;
		f->flags_plus = 0;
		f->width = 0;
		f->precision = -1;
		f->specifier = 0;
		f->sign = 0;
	}

	static void	parse_flags(const char *fmt, int *i, t_format *f)
	{
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
	}

	static void	parse_width(const char *fmt, int *i, t_format *f)
	{
		if (fmt[*i] >= '0' && fmt[*i] <= '9')
		{
			f->width = 0;
			while (fmt[*i] >= '0' && fmt[*i] <= '9')
				f->width = f->width * 10 + (fmt[(*i)++] - '0');
		}
	}

	static void	parse_precision(const char *fmt, int *i, t_format *f)
	{
		if (fmt[*i] == '.')
		{
			(*i)++;
			f->precision = 0;
			while (fmt[*i] >= '0' && fmt[*i] <= '9')
				f->precision = f->precision * 10 + (fmt[(*i)++] - '0');
		}
	}

	void	parse_format(const char *fmt, int *i, t_format *f)
	{
		init_format(f);
		(*i)++;
		parse_flags(fmt, i, f);
		parse_width(fmt, i, f);
		parse_precision(fmt, i, f);
		f->specifier = fmt[*i];
	}
