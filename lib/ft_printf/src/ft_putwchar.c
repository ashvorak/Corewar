/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:27:14 by oshvorak          #+#    #+#             */
/*   Updated: 2018/01/27 16:09:52 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static void	parse_2bytes(unsigned int v, unsigned int mask1, int fd)
{
	unsigned int octet;
	unsigned int o1;
	unsigned int o2;

	o2 = (v << 26) >> 26;
	o1 = ((v >> 6) << 27) >> 27;
	octet = (mask1 >> 8) | o1;
	write(fd, &octet, 1);
	octet = ((mask1 << 24) >> 24) | o2;
	write(fd, &octet, 1);
}

static void	parse_3bytes(unsigned int v, unsigned int mask2, int fd)
{
	unsigned int octet;
	unsigned int o1;
	unsigned int o2;
	unsigned int o3;

	o3 = (v << 26) >> 26;
	o2 = ((v >> 6) << 26) >> 26;
	o1 = ((v >> 12) << 28) >> 28;
	octet = (mask2 >> 16) | o1;
	write(fd, &octet, 1);
	octet = ((mask2 << 16) >> 24) | o2;
	write(fd, &octet, 1);
	octet = ((mask2 << 24) >> 24) | o3;
	write(fd, &octet, 1);
}

static void	parse_4bytes(unsigned int v, unsigned int mask3, int fd)
{
	unsigned int octet;
	unsigned int o1;
	unsigned int o2;
	unsigned int o3;
	unsigned int o4;

	o4 = (v << 26) >> 26;
	o3 = ((v >> 6) << 26) >> 26;
	o2 = ((v >> 12) << 26) >> 26;
	o1 = ((v >> 18) << 29) >> 29;
	octet = (mask3 >> 24) | o1;
	write(fd, &octet, 1);
	octet = ((mask3 << 8) >> 24) | o2;
	write(fd, &octet, 1);
	octet = ((mask3 << 16) >> 24) | o3;
	write(fd, &octet, 1);
	octet = ((mask3 << 24) >> 24) | o4;
	write(fd, &octet, 1);
}

void		ft_putwchar(wchar_t value, int bits, int fd)
{
	unsigned int	o;
	unsigned int	mask1;
	unsigned int	mask2;
	unsigned int	mask3;
	unsigned int	v;

	v = value;
	mask1 = 49280;
	mask2 = 14712960;
	mask3 = 4034953344;
	if (bits <= 7 || MB_CUR_MAX == 1)
	{
		o = value;
		write(fd, &o, 1);
	}
	else if (bits <= 11)
		parse_2bytes(v, mask1, fd);
	else if (bits <= 16)
		parse_3bytes(v, mask2, fd);
	else
		parse_4bytes(v, mask3, fd);
}
