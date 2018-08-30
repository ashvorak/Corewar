/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:34:34 by amazurok          #+#    #+#             */
/*   Updated: 2018/02/13 18:03:37 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_onechar(unsigned int v, int fd)
{
	write(fd, &v, 1);
	return (1);
}

static int	ft_twochar(unsigned int v, unsigned int mask1, int fd)
{
	unsigned char octet;
	unsigned char o2;
	unsigned char o1;

	o1 = ((v >> 6) << 27) >> 27;
	o2 = (v << 26) >> 26;
	octet = (mask1 >> 8) | o1;
	write(fd, &octet, 1);
	octet = ((mask1 << 24) >> 24) | o2;
	write(fd, &octet, 1);
	return (2);
}

static int	ft_threechar(unsigned int v, unsigned int mask2, int fd)
{
	unsigned char octet;
	unsigned char o3;
	unsigned char o2;
	unsigned char o1;

	o1 = ((v >> 12) << 28) >> 28;
	o2 = ((v >> 6) << 26) >> 26;
	o3 = (v << 26) >> 26;
	octet = (mask2 >> 16) | o1;
	write(fd, &octet, 1);
	octet = ((mask2 << 16) >> 24) | o2;
	write(fd, &octet, 1);
	octet = ((mask2 << 24) >> 24) | o3;
	write(fd, &octet, 1);
	return (3);
}

static int	ft_fourchar(unsigned int v, unsigned int mask3, int fd)
{
	unsigned char octet;
	unsigned char o4;
	unsigned char o3;
	unsigned char o2;
	unsigned char o1;

	o1 = ((v >> 18) << 29) >> 29;
	o2 = ((v >> 12) << 26) >> 26;
	o3 = ((v >> 6) << 26) >> 26;
	o4 = (v << 26) >> 26;
	octet = (mask3 >> 24) | o1;
	write(fd, &octet, 1);
	octet = ((mask3 << 8) >> 24) | o2;
	write(fd, &octet, 1);
	octet = ((mask3 << 16) >> 24) | o3;
	write(fd, &octet, 1);
	octet = ((mask3 << 24) >> 24) | o4;
	write(fd, &octet, 1);
	return (4);
}

int			ft_putuchar_fd(unsigned int octet, int fd)
{
	unsigned int	mask1;
	unsigned int	mask2;
	unsigned int	mask3;
	char			*tmp;
	size_t			k;

	mask1 = 49280;
	mask2 = 14712960;
	mask3 = 4034953344;
	tmp = ft_size2a_base(octet, 2);
	k = ft_strlen(tmp);
	if (k <= 7)
		ft_onechar(octet, fd);
	else if (k <= 11)
		ft_twochar(octet, mask1, fd);
	else if (k <= 16)
		ft_threechar(octet, mask2, fd);
	else
		ft_fourchar(octet, mask3, fd);
	ft_strdel(&tmp);
	return (k);
}
