/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:49:03 by oshvorak          #+#    #+#             */
/*   Updated: 2017/11/01 15:49:05 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nlen(int n)
{
	int num;

	num = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		num++;
		n = -n;
	}
	while (n != 0)
	{
		n /= 10;
		num++;
	}
	return (num);
}

char			*ft_itoa(int n)
{
	int			i;
	long long	x;
	int			num;
	char		*arr;

	i = -1;
	x = n;
	num = nlen(n);
	if (x == 0)
		return (ft_strsub("0", 0, 1));
	if (!(arr = ft_strnew(num)))
		return (NULL);
	if (x < 0)
	{
		arr[0] = '-';
		x = -x;
		i = 0;
	}
	while (--num > i)
	{
		arr[num] = (x % 10) + '0';
		x /= 10;
	}
	return (arr);
}
