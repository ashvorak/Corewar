/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:44:42 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/13 13:56:44 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

unsigned int	ft_chartoint(unsigned char *str)
{
	unsigned int	res;

	res = 0;
	res = res | str[0] << 24;
	res = res | str[1] << 16;
	res = res | str[2] << 8;
	res = res | str[3] << 0;
	return (res);
}

static t_player	read_magic(t_game *game, t_player *player, unsigned char buf[])
{
	player->magic = ft_chartoint(buf);
	player->magic != COREWAR_EXEC_MAGIC ?
	ft_error("Incorrect magic number", game) : 0;
	return (*player);
}

t_player		read_player(char *file, t_game *game)
{
	int				fd;
	t_player		player;
	unsigned char	buf[4];

	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error("There is no such file", game);
	ft_bzero(player.prog_name, sizeof(player.prog_name));
	ft_bzero(player.comment, sizeof(player.comment));
	read(fd, buf, 4);
	player = read_magic(game, &player, buf);
	read(fd, player.prog_name, sizeof(player.prog_name) - 1);
	read(fd, buf, 4);
	ft_chartoint(buf) ? ft_error("Name must be followed by NULL", game) : 0;
	read(fd, buf, 4);
	player.prog_size = ft_chartoint(buf);
	(player.prog_size > CHAMP_MAX_SIZE || player.prog_size == 0) ?
		ft_error("Champion have wrong size", game) : 0;
	read(fd, player.comment, sizeof(player.comment) - 1);
	read(fd, buf, 4);
	ft_chartoint(buf) ? ft_error("Comment must be followed by NULL", game) : 0;
	ft_bzero(player.opcode, MEM_SIZE / 6);
	read(fd, player.opcode, player.prog_size);
	if (read(fd, buf, 1) > 0)
		ft_error("Invalid program size", game);
	return (player);
}
