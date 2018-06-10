/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:28:02 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/09 18:22:27 by oshvorak         ###   ########.fr       */
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

int number;

typedef struct	s_area
{
	unsigned char	value;
	int				color;
	int         	PC;
	int             bold;
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
	int		label;
}				t_op;

typedef struct	s_process
{
	unsigned int		REG_NUM[REG_NUMBER];
	unsigned int		PC;
	int					carry;
	int					live;
	int					op_id;
	int                 color;
	int					CYCLE_TO_DONE;
	int                 num;
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
	int                 count_lives;
	int                 last_live;
	int                 lives_in_CP;
}				t_player;

typedef struct	s_game
{
	t_player		players[4];
	t_area			area[MEM_SIZE + 1];
	t_process		*process;
	int             num_proc;
	int             players_num;
	size_t			CYCLE;
	size_t          cycle_to_die;
	int             pause;
	int             speed;
	int             checks;
}				t_game;

void			ft_error(void);

t_game			*read_players(char **av, int ac, int i);
t_player		read_player(char *file);
void			fill_area(t_game *game);
void			push_procces(t_game *game, unsigned int location, unsigned int reg1, int num);
void			visual(t_game *game);
int				players_num(t_game *game);
int				check_codege(int op_id, int codage);
void			start_game(t_game *game);
void            clone_process(t_game *game, t_process *process, unsigned int location);

unsigned int    write_arg(t_process *process, t_game *game, int tt, int PC);
int				plus_PC(int codage, int MASK, int move);
void            my_pause(t_game *game);
void            manage_keys(t_game *game, int action);
int				push_op_id(unsigned char value);

void			op_aff(t_game *game, t_process *process);
void			op_zjmp(t_game *game, t_process *process);
void			op_sti(t_game *game, t_process *process);
void	        op_st(t_game *game, t_process *process);
void            op_and(t_game *game, t_process *process);
void            op_live(t_game *game, t_process *process);
void            op_add(t_game *game, t_process *process);
void            op_sub(t_game *game, t_process *process);
void            op_or(t_game *game, t_process *process);
void            op_xor(t_game *game, t_process *process);
void            op_fork(t_game *game, t_process *process);
void            op_lfork(t_game *game, t_process *process);
void			op_ld(t_game *game, t_process *process);
void			op_ldi(t_game *game, t_process *process);
void			op_lld(t_game *game, t_process *process);
void			op_lldi(t_game *game, t_process *process);

int				ret_arg(int codage, int MASK, int move);
int				jump_pc(unsigned char codage, int op_id);
unsigned int	write_2_bytes(t_game *game, int PC);
unsigned int	write_4_bytes(t_game *game, int PC);

static const t_op    op_tab[17] =
{
	{0, "live", "01", {T_DIR}, 1, 10, 0, 0, 4},
	{1, "ld", "02", {T_DIR | T_IND, T_REG}, 2, 5, 1, 0, 4},
	{2, "st", "03", {T_REG, T_IND | T_REG}, 2, 5, 1, 0, 4},
	{3, "add", "04", {T_REG, T_REG, T_REG}, 3, 10, 1, 0, 4},
	{4, "sub", "05", {T_REG, T_REG, T_REG}, 3, 10, 1, 0, 4},
	{5, "and", "06", {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 3, 6, 1, 0, 4},
	{6, "or", "07", {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 3, 6, 1, 0, 4},
	{7, "xor", "08", {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 3, 6, 1, 0, 4},
	{8, "zjmp", "09", {T_DIR}, 1, 20, 0, 1, 2},
	{9, "ldi", "0a", {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 3, 25, 1, 1, 2},
	{10, "sti", "0b", {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 3, 25, 1, 1, 2},
	{11, "fork", "0c", {T_DIR}, 1, 800, 0, 1, 2},
	{12, "lld", "0d", {T_DIR | T_IND, T_REG}, 2, 10, 1, 0, 4},
	{13, "lldi", "0e", {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 3, 50, 1, 1, 2},
	{14, "lfork", "0f", {T_DIR}, 1, 1000, 0, 1, 2},
	{15, "aff", "10", {T_REG}, 1, 2, 1, 0, 4},
	{16, 0, 0, {0}, 0, 0, 0, 0, 0}
};

#endif