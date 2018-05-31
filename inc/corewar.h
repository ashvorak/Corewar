/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:28:02 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/30 16:54:25 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../lib/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/ft_printf/inc/ft_printf.h"

#include "op.h"

typedef struct	s_area
{
	char		*value;
	int			color;
	int			pc;
}				t_area;

typedef struct	s_player
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
	char				**opcode;
	int					color;
}				t_player;

typedef struct	s_game
{
	t_player	players[4];
	t_area	area[MEM_SIZE + 1];
}				t_game;

void			ft_error(void);

void			read_players(t_game *game, char **av, int ac, int i);
t_player		read_player(char *file);
void			visual(t_game *game);
int				what_color(int col);

#endif