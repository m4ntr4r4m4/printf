/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:40:19 by ahammoud          #+#    #+#             */
/*   Updated: 2021/11/22 01:51:46 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putnbr_base(unsigned long long num, int fd, char *base)
{
	int		i;
	int		len;

	len = ft_strlen(base);
	i = 0;
	if (num >= (unsigned long long)len)
		 i += ft_putnbr_base(num / len, fd, base);
	ft_putchar_fd(base[(num % len)], fd);
	i += 1;
	return (i);
}
