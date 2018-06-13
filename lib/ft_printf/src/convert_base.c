/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 13:08:39 by oshvorak          #+#    #+#             */
/*   Updated: 2018/01/27 16:02:10 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	take_size(char type)
{
	if (type == 'b')
		return (2);
	if (type == 'o' || type == 'O')
		return (8);
	if (type == 'u' || type == 'U')
		return (10);
	else
		return (16);
}

static int	wlen(size_t value, int base)
{
	int num;

	num = 0;
	while (value)
	{
		value /= base;
		num++;
	}
	return (num);
}

char		*convert_base(size_t value, t_spec *spec)
{
	int		i;
	int		base;
	int		buf;
	char	*res;

	if (value == 0)
		return (ft_strsub("0", 0, 1));
	base = take_size(spec->type);
	i = wlen(value, base);
	if (!(res = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	res[i] = '\0';
	while (value)
	{
		buf = value % base;
		if (buf > 9)
			if (spec->type == 'x' || spec->type == 'p')
				res[--i] = buf + 87;
			else
				res[--i] = buf + 55;
		else
			res[--i] = buf + '0';
		value /= base;
	}
	return (res);
}
