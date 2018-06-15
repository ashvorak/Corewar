/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 13:16:10 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/14 22:41:22 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	execute_process(t_game *game, t_process *process)
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
	else if (process->op_id == 12)
		op_lld(game, process);
	else if (process->op_id == 13)
		op_lldi(game, process);
	else if (process->op_id == 14)
		op_lfork(game, process);
	else if (process->op_id == 15)
		op_aff(game, process);
}

int		processes_number(t_process *process)
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

void	my_pause(t_game *game)
{
	int s;

	s = -1;
	game->pause = 1;
	while (1)
	{
		s = (game->flags.v) ? getch() : -1;
		if (s == 32)
		{
			game->pause = 0;
			break ;
		}
		else if (s == 27)
		{
			(game->flags.v) ? endwin() : 1;
			exit(0);
		}
		(game->flags.v) ? visual(game) : 1;
	}
}

void	manage_keys(t_game *game, int action)
{
	if (action == 32 || game->pause == 1)
		my_pause(game);
	else if (action == 27)
	{
		(game->flags.v) ? endwin() : 1;
		exit_game(game);
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
	int			action;
	int			i;

	action = -1;
	process = game->process;
	while (process)
	{
		process->op_id = push_op_id(game->area[process->pc].value);
		process = process->next;
	}
	i = 1;
	while (game->process)
	{
		(game->flags.v) ? manage_keys(game, action) : 1;
		execute(game);
		if (game->flags.dump > 0 && game->cycle == game->flags.dump)
			dump_memory(game);
		game->cycle++;
		(game->flags.c) ? ft_printf("Cycle: %zu\n", game->cycle) : 0;
		if (i % game->cycle_to_die == 0)
			i = check_procces(game);
		game->num_proc = processes_number(game->process);
		(game->flags.v) ? visual(game) : 1;
		action = (game->flags.v) ? getch() : -1;
		i++;
	}
}
