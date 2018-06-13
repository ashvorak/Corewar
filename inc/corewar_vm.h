/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:28:02 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/13 14:14:14 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
# define COREWAR_VM_H

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

# define COLOR_GREY 8

int						g_number;

typedef struct			s_fla
{
	int					v;
	int					n;
	size_t				dump;
}						t_fla;

typedef struct			s_area
{
	unsigned char		value;
	int					color;
	int					pc;
	int					bold;
	int					player;
}						t_area;

typedef struct			s_op
{
	int					id;
	char				*hex;
	int					arg_type[3];
	int					arg;
	int					cycles;
	int					label;
}						t_op;

typedef struct			s_process
{
	unsigned int		reg_num[REG_NUMBER];
	unsigned int		pc;
	int					carry;
	int					live;
	int					op_id;
	int					color;
	int					cycle_to_done;
	int					num;
	struct s_process	*next;
}						t_process;

typedef struct			s_player
{
	int					id;
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
	unsigned char		opcode[MEM_SIZE / 6];
	int					color;
	int					live;
	int					n;
	int					count_lives;
	int					last_live;
	int					lives_in_cp;
}						t_player;

typedef struct			s_game
{
	t_player			players[4];
	t_fla				flags;
	t_area				area[MEM_SIZE + 1];
	t_process			*process;
	int					num_proc;
	int					players_num;
	size_t				cycle;
	size_t				cycle_to_die;
	int					pause;
	unsigned int		n;
	int					speed;
	int					checks;
	int					winner;
	int					finish;
}						t_game;

void	                ft_error(char *str, t_game *game);
void					create_fla(t_fla *flag);
int						flags_read(char **argv, int argc, t_fla *flag);
t_game					*read_players(char **av, int ac, int i);
t_player				read_player(char *file, t_game *game);
void					fill_area(t_game *game);
void					push_procces(t_game *game, \
unsigned int location, unsigned int reg1, int num);
void					visual(t_game *game);
int						players_num(t_game *game);
int						check_codege(int op_id, int codage);
void					start_game(t_game *game);
void					clone_process(t_game *game, \
t_process *process, unsigned int location);
void					print_frame(WINDOW *stdscr, int speed);
void					initialize_colors(void);
void					print_data(t_game *game);
void					right_menu(t_game *game);
int						what_color(int col);
int						check_procces(t_game *game);
void					execute_process(t_game *game, t_process *process);
int						check_reg_ind(t_game *game, t_process *process, int in);
int						get_first_reg(int n, t_game *game, int pos);
void					dump_memory(t_game *game);
void					finish_game(t_game *game);
void					show_players(t_game *game);
void	                init(t_game *game);
void                    exit_game(t_game *game);

unsigned int			write_arg(t_process *process, \
t_game *game, int tt, int pc);
int						plus_pc(int codage, int mask, int move);
void					my_pause(t_game *game);
void					manage_keys(t_game *game, int action);
int						push_op_id(unsigned char value);

void					op_aff(t_game *game, t_process *process);
void					op_zjmp(t_game *game, t_process *process);
void					op_sti(t_game *game, t_process *process);
void					op_st(t_game *game, t_process *process);
void					op_and(t_game *game, t_process *process);
void					op_live(t_game *game, t_process *process);
void					op_add(t_game *game, t_process *process);
void					op_sub(t_game *game, t_process *process);
void					op_or(t_game *game, t_process *process);
void					op_xor(t_game *game, t_process *process);
void					op_fork(t_game *game, t_process *process);
void					op_lfork(t_game *game, t_process *process);
void					op_ld(t_game *game, t_process *process);
void					op_ldi(t_game *game, t_process *process);
void					op_lld(t_game *game, t_process *process);
void					op_lldi(t_game *game, t_process *process);

int						ret_arg(int codage, int mask, int move);
int						jump_pc(unsigned char codage, int op_id);
unsigned int			write_2_bytes(t_game *game, int pc);
unsigned int			write_4_bytes(t_game *game, int pc);
void					execute(t_game *game);
void					ft_usage(void);

static const t_op		g_op_tab[17] =
{
	{0, "01", {T_DIR}, 1, 10, 4},
	{1, "02", {T_DIR | T_IND, T_REG}, 2, 5, 4},
	{2, "03", {T_REG, T_IND | T_REG}, 2, 5, 4},
	{3, "04", {T_REG, T_REG, T_REG}, 3, 10, 4},
	{4, "05", {T_REG, T_REG, T_REG}, 3, 10, 4},
	{5, "06", {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 3, 6, 4},
	{6, "07", {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 3, 6, 4},
	{7, "08", {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 3, 6, 4},
	{8, "09", {T_DIR}, 1, 20, 2},
	{9, "0a", {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 3, 25, 2},
	{10, "0b", {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 3, 25, 2},
	{11, "0c", {T_DIR}, 1, 800, 2},
	{12, "0d", {T_DIR | T_IND, T_REG}, 2, 10, 4},
	{13, "0e", {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 3, 50, 2},
	{14, "0f", {T_DIR}, 1, 1000, 2},
	{15, "10", {T_REG}, 1, 2, 4},
	{16, 0, {0}, 0, 0, 0}
};

#endif
