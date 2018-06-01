/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:28:02 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/01 14:08:54 by oshvorak         ###   ########.fr       */
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
	char	*name;
	int		arg;
	int		id;
	int		CYCLES;
	int		codage;
	int		carry;
}				t_op;

typedef struct	s_process
{
	int					location;
	int					live;
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

static const t_op    op_tab[17] =
{
	{"live", 1, 1, 10, 0, 0},
	{"ld", 2, 2, 5, 1, 0},
	{"st", 2, 3, 5, 1, 0},
	{"add", 3, 4, 10, 1, 0},
	{"sub", 3, 5, 10, 1, 0},
	{"and", 3, 6, 6, 1, 0},
	{"or", 3, 7, 6, 1, 0},
	{"xor", 3, 8, 6, 1, 0},
	{"zjmp", 1, 9, 20, 0, 1},
	{"ldi", 3, 10, 25, 1, 1},
	{"sti", 3, 11, 25, 1, 1},
	{"fork", 1, 12, 800, 0, 1},
	{"lld", 2, 13, 10, 1, 0},
	{"lldi", 3, 14, 50, 1, 1},
	{"lfork", 1, 15, 1000, 0, 1},
	{"aff", 1, 16, 2, 1, 0},
	{0, 0, 0, 0, 0, 0}
};

#endif