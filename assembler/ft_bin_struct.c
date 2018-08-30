/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aryabenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 11:14:45 by aryabenk          #+#    #+#             */
/*   Updated: 2018/05/31 18:06:06 by aryabenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_write.h"

t_bin	*ft_create_bin(t_bin *bin)
{
	bin = (t_bin*)malloc(sizeof(t_bin));
	bin->i = 0;
	bin->size = 0;
	bin->j = 0;
	bin->res = NULL;
	bin->oldsize = 0;
	bin->bytelen = 0;
	bin->opr = 0;
	bin->progsize = 0;
	return (bin);
}

void	ft_del_bin(t_bin *bin)
{
	free(bin->res);
	bin->res = NULL;
	free(bin);
}
