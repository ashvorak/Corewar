/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 10:50:20 by aryabenk          #+#    #+#             */
/*   Updated: 2018/05/30 11:29:37 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_write.h"

void	ft_add_2_bytenum(ssize_t num, t_bin *bin)
{
	bin->res[bin->i] = (t_uchar)(num >> 8);
	bin->i++;
	bin->res[bin->i] = (t_uchar)(num >> 0);
	bin->i++;
}

void	ft_add_4_bytenum(ssize_t num, t_bin *bin)
{
	bin->res[bin->i] = (t_uchar)(num >> 24);
	bin->i++;
	bin->res[bin->i] = (t_uchar)(num >> 16);
	bin->i++;
	bin->res[bin->i] = (t_uchar)(num >> 8);
	bin->i++;
	bin->res[bin->i] = (t_uchar)(num >> 0);
	bin->i++;
}
