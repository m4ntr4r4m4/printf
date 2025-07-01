/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m4ntr4 <m4ntr4@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by m4ntr4            #+#    #+#             */
/*   Updated: 2025/07/01 04:51:10 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

char	*utoa_base(unsigned long long num, const char *base)
{
	unsigned long long		tmp;
	int						base_len;
	int						len;
	char					*str;

	tmp = num;
	base_len = ft_strlen((char *)base);
	len = 1;
	while (tmp >= (unsigned long long)base_len)
	{
		tmp /= base_len;
		len++;
	}
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (len-- > 0)
	{
		str[len] = base[num % base_len];
		num /= base_len;
	}
	return (str);
}

int	put_chars(char c, int count)
{
	int	sum;

	sum = 0;
	while (count-- > 0)
		sum += ft_putcharf(c);
	return (sum);
}
