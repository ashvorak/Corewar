/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 13:16:10 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/07 13:16:10 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

static void	execute_process(t_game *game, t_process *process)
{
	if (process->op_id == 0)
		op_live(game, process);
	else if (process->op_id == 1)
		op_ld(game, process);
	else if (process->op_id == 2)
		op_st(game, process);
	else if (process->op_id == 3)
		op_add(game, process);
	else if (process->op_id == 4)
		op_sub(game, process);
	else if (process->op_id == 5)
		op_and(game, process);
	else if (process->op_id == 6)
		op_or(game, process);
	else if (process->op_id == 7)
		op_xor(game, process);
	else if (process->op_id == 8)
		op_zjmp(game, process);
	else if (process->op_id == 9)
		op_ldi(game, process);
	else if (process->op_id == 10)
		op_sti(game, process);
	else if (process->op_id == 11)
		op_fork(game, process);
	else if (process->op_id == 14)
		op_lfork(game, process);
	else if (process->op_id == 15)
		op_aff(game, process);
}

int	push_op_id(unsigned char value)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (value == op_tab[i].id + 1)
			return (op_tab[i].id);
		i++;
	}
	return (16);
}

static void	execute(t_game *game)
{
	t_process *process;
	int			action;

	process = game->process;
	while (process)
	{
		manage_keys(game, action);
		if (process->op_id != 16)
		{
			if (process->CYCLE_TO_DONE == op_tab[process->op_id].CYCLES)
			{
				execute_process(game, process);
				process->op_id = 16;
				process->CYCLE_TO_DONE = 1;
			}
			else
				process->CYCLE_TO_DONE++;
		}
		else
		{
			game->area[process->PC].PC = 0;
			process->PC += process->PC + 1 == MEM_SIZE ? -process->PC : 1;
		}
		process->op_id = push_op_id(game->area[process->PC].value);
		game->area[process->PC].PC = 1;
		process = process->next;
		action = getch();
	}
}

static void check_procces(t_game *game)
{
	t_process *tmp;

	tmp = game->process;
	while (tmp)
	{
		if (!tmp->live)
		{
			if (tmp->prev)
			{
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				free(tmp);
				tmp = NULL;
			}
			else
			{
				game->process = tmp->next;
				if (tmp->next)
					tmp->next->prev = NULL;
				free(tmp);
				tmp = game->process;
			}
		}
		else
		{
			tmp->live = 0;
			tmp = tmp->next;
		}
	}
}

int     processes_number(t_process *process)
{
	int i;
	
	i = 0;
	while (process)
	{
		i++;
		process = process->next;
	}
	return (i);
}

void    my_pause(t_game *game)
{
	int s;
	
	s = -1;
	game->pause = 1;
	while (1)
	{
		s = getch();
		if (s == 32)
		{
			game->pause = 0;
			break;
		}
		else if (s == 27)
		{
			endwin();
			exit(0);
		}
		visual(game);
	}
}

void    manage_keys(t_game *game, int action)
{
	if (action == 32 || game->pause == 1)
		my_pause(game);
	else if (action == 27)
	{
		endwin();
		exit(0);
	}
	else if (action == 43)
	{
		game->speed -= 132;
		game->speed = (game->speed < 30) ? 30 : game->speed;
	}
	else if (action == 45)
	{
		game->speed += 132;
		game->speed = (game->speed > 4000) ? 4000 : game->speed;
	}
}

void	start_game(t_game *game)
{
	t_process	*process;
	int         action;
	
	game->pause = 1;
	game->speed = 2000;
	action = -1;
	game->cycle_to_die = CYCLE_TO_DIE;
	process = game->process;
	while (process)
	{
		process->op_id = push_op_id(game->area[process->PC].value);
		process = process->next;
	}
	while (game->process && game->CYCLE < 30000)
	{
		manage_keys(game, action);
		execute(game);
		game->CYCLE++;
		//game->num_proc = processes_number(game->process);
		if (game->CYCLE % game->cycle_to_die == 0)
			check_procces(game);
		game->num_proc = processes_number(game->process);
		visual(game);
		action = getch();
		//ft_printf("action: %d\n", action);
	}
}
