/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:28:02 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/04 11:27:06 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <ncurses.h>
# include "../lib/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/ft_printf/inc/ft_printf.h"

# include "op.h"

# define MASK_1 192
# define MASK_2 48
# define MASK_3 12

typedef struct	s_area
{
	unsigned char	value;
	int				color;
	int         	PC;
	int             player;
}				t_area;

typedef struct	s_op
{
	int		id;
	char	*name;
	char	*hex;
	int		arg_type[3];
	int		arg;
	int		CYCLES;
	int		codage;
	int		carry;
}				t_op;

typedef struct	s_process
{
	unsigned int		REG_NUM[REG_NUMBER];
	int					PC;
	int					carry;
	int					live;
	int					op_id;
	int					CYCLE_TO_DONE;
	struct s_process	*next;
}				t_process;

typedef struct	s_player
{
	int 				id;
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
	unsigned char		opcode[MEM_SIZE / 6];
	int					color;
	int                 live;
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
int				check_codege(int op_id, int codage);
void			start_game(t_game *game);

char		    *convert(size_t value);

void			op_aff(t_game *game, t_process *process);
void			op_zjmp(t_game *game, t_process *process);
void			op_sti(t_game *game, t_process *process);
void            op_and(t_game *game, t_process *process);
void            op_live(t_game *game, t_process *process);
void            op_add(t_game *game, t_process *process);
void            op_sub(t_game *game, t_process *process);

int				ret_arg(int codage, int MASK, int move);
unsigned int	write_2_bytes(t_game *game, int PC);
unsigned int	write_4_bytes(t_game *game, int PC);

static const t_op    op_tab[17] =
{
	{0, "live", "01", {T_DIR}, 1, 10, 0, 0},
	{1, "ld", "02", {T_DIR | T_IND, T_REG}, 2, 5, 1, 0},
	{2, "st", "03", {T_REG, T_IND | T_REG}, 2, 5, 1, 0},
	{3, "add", "04", {T_REG, T_REG, T_REG}, 3, 10, 1, 0},
	{4, "sub", "05", {T_REG, T_REG, T_REG}, 3, 10, 1, 0},
	{5, "and", "06", {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 3, 6, 1, 0},
	{6, "or", "07", {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 3, 6, 1, 0},
	{7, "xor", "08", {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 3, 6, 1, 0},
	{8, "zjmp", "09", {T_DIR}, 1, 20, 0, 1},
	{9, "ldi", "0a", {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 3, 25, 1, 1},
	{10, "sti", "0b", {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 3, 25, 1, 1},
	{11, "fork", "0c", {T_DIR}, 1, 800, 0, 1},
	{12, "lld", "0d", {T_DIR | T_IND, T_REG}, 2, 10, 1, 0},
	{13, "lldi", "0e", {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 3, 50, 1, 1},
	{14, "lfork", "0f", {T_DIR}, 1, 1000, 0, 1},
	{15, "aff", "10", {T_REG}, 1, 2, 1, 0},
	{16, 0, 0, {0}, 0, 0, 0, 0}
};

#endif