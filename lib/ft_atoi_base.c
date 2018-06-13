/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 12:59:34 by oshvorak          #+#    #+#             */
/*   Updated: 2018/04/04 13:01:31 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ret_base(char c)
{
	int res;

	if (c >= '0' && c <= '9')
		res = c - '0';
	else if (c >= 'a' && c <= 'z')
		res = c - 'a' + 10;
	else if (c >= 'A' && c <= 'Z')
		res = c - 'A' + 10;
	else
		res = -1;
	return (res);
}

int	ft_atoi_base(const char *str, int base)
{
	int res;
	int sign;
	int tmp;

	res = 0;
	if (base <= 1 || base > 16)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
						|| *str == '\r' || *str == '\v')
		str++;
	sign = *str == '-' ? -1 : 1;
	*str == '-' || *str == '+' ? str++ : 0;
	tmp = ret_base(*str);
	while (tmp >= 0 && tmp < base)
	{
		res = res * base + tmp;
		str++;
		tmp = ret_base(*str);
	}
	return (res * sign);
}
