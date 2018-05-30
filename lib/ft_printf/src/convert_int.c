/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 13:08:39 by oshvorak          #+#    #+#             */
/*   Updated: 2018/01/27 16:04:51 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	wlen(ssize_t value)
{
	int num;

	num = 0;
	if (value < 0)
	{
		value = -value;
		num++;
	}
	while (value)
	{
		value /= 10;
		num++;
	}
	return (num);
}

char		*convert_int(ssize_t value)
{
	int		i;
	size_t	uvalue;
	char	*res;

	if (value == 0)
		return (ft_strsub("0", 0, 1));
	i = wlen(value);
	if (!(res = ft_strnew(i)))
		return (NULL);
	if (value < 0)
	{
		uvalue = -value;
		res[0] = '-';
	}
	else
		uvalue = value;
	while (uvalue)
	{
		res[--i] = uvalue % 10 + '0';
		uvalue /= 10;
	}
	return (res);
}
