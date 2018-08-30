/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 13:16:10 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/15 17:14:34 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void			my_pause(t_game *game)
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

void			manage_keys(t_game *game, int action)
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

void			set_pc(t_game *game)
{
	t_process *pr;

	pr = game->process;
	while (pr)
	{
		game->area[pr->pc].pc = 1;
		pr = pr->next;
	}
}

static void		cycle_op_id(t_game *game)
{
	t_process	*process;

	process = game->process;
	while (process)
	{
		process->op_id = push_op_id(game->area[process->pc].value);
		process = process->next;
	}
}

void			start_game(t_game *game)
{
	int			action;
	int			i;

	action = -1;
	cycle_op_id(game);
	i = 1;
	while (game->process && game->cycle_to_die > 0)
	{
		(game->flags.v) ? manage_keys(game, action) : 1;
		game->cycle++;
		execute(game);
		set_pc(game);
		if (game->flags.dump > 0 && game->cycle == game->flags.dump)
			dump_memory(game);
		(game->flags.c && !game->flags.v) ? ft_printf("Cycle: %zu\n",
			game->cycle) : 0;
		if (i % game->cycle_to_die == 0)
			i = check_procces(game);
		game->num_proc = processes_number(game);
		(game->flags.v) ? visual(game) : 1;
		action = (game->flags.v) ? getch() : -1;
		i++;
	}
	finish_game(game);
}
