/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:47:48 by aryabenk          #+#    #+#             */
/*   Updated: 2018/06/12 16:51:44 by amazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_write.h"

int	ft_write(t_header data, t_label *a, char *filename)
{
	t_bin		*bin;
	ssize_t		size;

	bin = ft_create_bin(NULL);
	bin->size = PROG_NAME_LENGTH + COMMENT_LENGTH + sizeof(data.magic) \
		+ sizeof(data.prog_size) + 8;
	ft_add_basic(data, bin);
	size = bin->size;
	ft_add_opcode(bin, a);
	bin->i = bin->progsize;
	ft_add_num(bin, (t_uint)(bin->size - size));
	ft_print_result(filename, bin->res, bin->size);
	ft_del_bin(bin);
	return (0);
}
