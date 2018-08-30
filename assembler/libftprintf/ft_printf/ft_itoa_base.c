/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 12:21:44 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/02 16:56:45 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_intlen(size_t val, int base)
{
	int i;

	i = 0;
	if (!val)
		return (1);
	while (val)
	{
		val /= base;
		i++;
	}
	return (i);
}

char			*ft_size2a_base(size_t value, int base)
{
	size_t	uval;
	int		tmp;
	int		size;
	char	*res;

	size = 0;
	uval = size ? -value : (size_t)value;
	size += ft_intlen(uval, base);
	res = ft_strnew(size);
	while (size > 0)
	{
		tmp = uval % base;
		if (tmp > 9)
			res[--size] = tmp + 'a' - 10;
		else
			res[--size] = tmp + '0';
		uval /= base;
	}
	return (res);
}

char			*ft_ssize2a_base(ssize_t value, int base)
{
	size_t	uval;
	int		tmp;
	int		size;
	char	*res;

	size = (base == 10 && value < 0) ? 1 : 0;
	uval = size ? (size_t)-value : (size_t)value;
	size += ft_intlen(uval, base);
	res = ft_strnew(size);
	while (size > 0)
	{
		tmp = uval % base;
		if (tmp > 9)
			res[--size] = tmp + 'a' - 10;
		else
			res[--size] = tmp + '0';
		uval /= base;
	}
	res[0] = (base == 10 && value < 0) ? '-' : res[0];
	return (res);
}
