/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:58:32 by ahammoud          #+#    #+#             */
/*   Updated: 2025/07/01 04:02:02 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_sum(t_ptr ptr, int prefix_len, int prefix)
{
	int	i;

	if (prefix_len)
	{
		ptr.sum += ft_putcharf('0');
		ptr.sum += ft_putcharf(prefix);
	}
	ptr.sum += put_chars('0', ptr.ppad);
	i = 0;
	while (i < (int)ft_strlen(ptr.str))
		ptr.sum += ft_putcharf(ptr.str[i++]);
	ptr.sum += put_chars(' ', ptr.spad);
	return (ptr.sum);
}

int	ft_sum2(t_ptr ptr, int prefix_len, int prefix)
{
	int	i;

	ptr.sum += put_chars(' ', ptr.spad);
	if (prefix_len)
	{
		ptr.sum += ft_putcharf('0');
		ptr.sum += ft_putcharf(prefix);
	}
	ptr.sum += put_chars('0', ptr.ppad);
	i = 0;
	while (i < (int)ft_strlen(ptr.str))
		ptr.sum += ft_putcharf(ptr.str[i++]);
	return (ptr.sum);
}
