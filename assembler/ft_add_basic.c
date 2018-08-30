/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:50:38 by aryabenk          #+#    #+#             */
/*   Updated: 2018/05/31 18:06:06 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_write.h"

void	ft_arr2null(t_bin *bin)
{
	int i;

	i = 0;
	while (i < bin->size)
		bin->res[i++] = 0;
	bin->res[i] = '\0';
}

void	ft_add_num(t_bin *bin, t_uint num)
{
	int k;
	int count;

	count = 0;
	k = 24;
	while (count < 4)
	{
		bin->res[bin->i] = (t_uchar)(num >> k);
		k -= 8;
		bin->i++;
		count++;
	}
}

void	ft_add_name(t_bin *bin, t_header data)
{
	int j;

	j = 0;
	while (j < PROG_NAME_LENGTH)
	{
		bin->res[bin->i] = (t_uchar)data.prog_name[j++];
		bin->i++;
	}
}

void	ft_add_comment(t_bin *bin, t_header data)
{
	int j;

	j = 0;
	while (j < COMMENT_LENGTH)
	{
		bin->res[bin->i] = (t_uchar)data.comment[j++];
		bin->i++;
	}
}

void	ft_add_basic(t_header data, t_bin *bin)
{
	bin->res = (t_uchar*)malloc(sizeof(t_uchar) * bin->size + 1);
	ft_arr2null(bin);
	ft_add_num(bin, data.magic);
	ft_add_name(bin, data);
	ft_add_num(bin, 0);
	bin->progsize = bin->i;
	ft_add_num(bin, data.prog_size);
	ft_add_comment(bin, data);
}
