/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:44:42 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/09 18:26:09 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

unsigned	int	ft_chartoint(unsigned char *str)
{
	unsigned int	res;

	res = 0;
	res = res | str[0] << 24;
	res = res | str[1] << 16;
	res = res | str[2] << 8;
	res = res | str[3] << 0;
	return (res);
}

t_player		read_player(char *file)
{
	int				fd;
	t_player		player;
	unsigned char	buf[4];
	unsigned char	buf1[4];

	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error();
	read(fd, buf, 4);
	read(fd, player.prog_name, 128);
	lseek(fd, 136, 0);
	read(fd, buf1, 4);
	read(fd, player.comment, 2048);
	lseek(fd, 2192, 0);
	player.magic = ft_chartoint(buf);
	player.prog_size = ft_chartoint(buf1);
	ft_bzero(player.opcode, MEM_SIZE / 6);
	read(fd, player.opcode, player.prog_size);
	if (read(fd, buf, 1) > 0)
		ft_error();
	return (player);
}
