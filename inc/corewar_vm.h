/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:28:02 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/01 14:58:26 by oshvorak         ###   ########.fr       */
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
	int			REG_NUM;
	int			PC;
	int			carry;
}				t_area;

typedef struct	s_op
{
	int		id;
	char	*name;
	int		arg;
	int		CYCLES;
	int		codage;
	int		carry;
}				t_op;

typedef struct	s_process
{
	int					location;
	int					live;
	int					op_id;
	char				REG[REG_SIZE];
	char				IND[IND_SIZE];
	char				DIR[DIR_CODE];
	int					CYCLE_TO_DONE;
	struct s_process	*next;
}				t_process;

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
	t_player		players[4];
	t_area			area[MEM_SIZE + 1];
	t_process		*process;
	size_t			CYCLE;
}				t_game;

void			ft_error(void);

t_game			*read_players(char **av, int ac, int i);
t_player		read_player(char *file);
void			fill_area(t_game *game);
void			push_procces(t_game *game, int location);
void			visual(t_game *game);
int				players_num(t_game *game);

static const t_op    op_tab[17] =
{
	{1, "live", 1, 10, 0, 0},
	{2, "ld", 2, 5, 1, 0},
	{3, "st", 2, 5, 1, 0},
	{4, "add", 3, 10, 1, 0},
	{5, "sub", 3, 10, 1, 0},
	{6, "and", 3, 6, 1, 0},
	{7, "or", 3, 6, 1, 0},
	{8, "xor", 3, 6, 1, 0},
	{9, "zjmp", 1, 20, 0, 1},
	{10, "ldi", 3, 25, 1, 1},
	{11, "sti", 3, 25, 1, 1},
	{12, "fork", 1, 800, 0, 1},
	{13, "lld", 2, 10, 1, 0},
	{14, "lldi", 3, 50, 1, 1},
	{15, "lfork", 1, 1000, 0, 1},
	{16, "aff", 1, 2, 1, 0},
	{0, 0, 0, 0, 0, 0}
};

#endif