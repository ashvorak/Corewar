/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 17:08:35 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/16 17:08:41 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char		*ft_itoa_base(size_t value, int base)
{
	int		i;
	int		buf;
	char	*res;

	if (value == 0)
		return (ft_strsub("0", 0, 1));
	i = wlen(value, base);
	if (!(res = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	res[i] = '\0';
	while (value)
	{
		buf = value % base;
		if (buf > 9)
			res[--i] = buf + 87;
		else
			res[--i] = buf + '0';
		value /= base;
	}
	return (res);
}
