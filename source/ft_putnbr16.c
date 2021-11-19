/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr16.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:41:47 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/19 11:52:37 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putnbr_16(long nbr, int	x)
{
	char	*base;
	long	i;
	long	num[50];

	i = 0;
	if (x == 1)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nbr < 0)
	{
		nbr = nbr * -1;
		ft_putchar_fd('-', 1);
	}
	while (nbr)
	{
		num[i] = nbr % 16;
		nbr = nbr / 16;
		i++;
	}
		while (--i >= 0)
			ft_putchar_fd(base[num[i]], 1);
}
