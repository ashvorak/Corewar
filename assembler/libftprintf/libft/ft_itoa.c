/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 19:04:41 by amazurok          #+#    #+#             */
/*   Updated: 2017/11/06 13:06:05 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	neg(char *res, long long *n)
{
	if (*n < 0)
	{
		res[0] = '-';
		*n = (*n) * -1;
		return (1);
	}
	return (0);
}

char		*ft_itoa(int i)
{
	char		*res;
	long long	n;
	int			len;
	int			j;

	len = 1;
	j = 0;
	n = i;
	if (n == 0)
		return (ft_strsub("0", 0, 1));
	while (i /= 10)
		len++;
	if (n < 0)
		len++;
	if (!(res = ft_strnew(len)))
		return (NULL);
	if (neg(res, &n))
		j++;
	while (n)
	{
		res[--len] = n % 10 + '0';
		n = n / 10;
	}
	return (res);
}
