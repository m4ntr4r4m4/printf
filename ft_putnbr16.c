/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr16.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:41:47 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/18 12:54:26 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putnbr_16(int nbr)
{
	char	base[] = "0123456789abcdef";
	int	i;
	int	num[50];

	i = 0;
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
