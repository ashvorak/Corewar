/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:44:42 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/12 13:49:39 by amazurok         ###   ########.fr       */
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

	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error("There is no such file");
	ft_bzero(player.prog_name, sizeof(player.prog_name));
	ft_bzero(player.comment, sizeof(player.comment));
	read(fd, buf, 4);
	player.magic = ft_chartoint(buf);
	player.magic != COREWAR_EXEC_MAGIC ? ft_error("Incorrect magic number") : 0;
	read(fd, player.prog_name, sizeof(player.prog_name) - 1);
	read(fd, buf, 4);
	ft_chartoint(buf) ? ft_error("Name must be followed by NULL") : 0;
	read(fd, buf, 4);
	player.prog_size = ft_chartoint(buf);
	read(fd, player.comment, sizeof(player.comment) - 1);
	read(fd, buf, 4);
	ft_chartoint(buf) ? ft_error("Comment must be followed by NULL") : 0;
	ft_bzero(player.opcode, MEM_SIZE / 6);
	read(fd, player.opcode, player.prog_size);
	if (read(fd, buf, 1) > 0)
		ft_error("Invalid program size");
	return (player);
}
