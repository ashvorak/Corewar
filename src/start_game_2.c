/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:45:31 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/15 20:07:25 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int				push_op_id(unsigned char value)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (value == g_op_tab[i].id + 1)
			return (g_op_tab[i].id);
		i++;
	}
	return (16);
}

static	void	execute_add(t_game *game, t_process *process)
{
	if (process->op_id != 16)
	{
		if (process->cycle_to_done == g_op_tab[process->op_id].cycles)
		{
			execute_process(game, process);
			process->op_id = 16;
			process->cycle_to_done = 1;
		}
		else
			process->cycle_to_done++;
	}
	else
	{
		game->area[process->pc].pc = 0;
		process->pc += process->pc + 1 == MEM_SIZE ? -process->pc : 1;
	}
}

void			execute(t_game *game)
{
	t_process	*process;
	int			action;

	action = -1;
	process = game->process;
	while (process)
	{
		if (game->flags.v)
			manage_keys(game, action);
		execute_add(game, process);
		if (process->op_id == 16)
			process->op_id = push_op_id(game->area[process->pc].value);
		process = process->next;
		if (game->flags.v)
			action = getch();
	}
}

static void		check_process_add(t_game *game, t_process *tmp, t_process *buf)
{
	while (tmp)
		if (!tmp->live)
		{
			game->area[tmp->pc].pc = 0;
			if (buf)
			{
				buf->next = tmp->next;
				free(tmp);
				tmp = buf->next;
			}
			else
			{
				game->process = tmp->next;
				free(tmp);
				tmp = game->process;
			}
		}
		else
		{
			tmp->live = 0;
			buf = tmp;
			tmp = tmp->next;
		}
}

int				check_procces(t_game *game)
{
	t_process	*tmp;
	t_process	*buf;
	int			i;

	game->checks++;
	tmp = game->process;
	buf = NULL;
	check_process_add(game, tmp, buf);
	i = 0;
	while (i++ < game->players_num)
	{
		if (game->live_count >= 21 || game->checks == MAX_CHECKS)
		{
			game->cycle_to_die -= CYCLE_DELTA;
			game->checks = 0;
			break ;
		}
	}
	while (--i >= 0)
	{
		game->players[i].count_lives = 0;
		game->players[i].lives_in_cp = 0;
	}
	game->live_count = 0;
	return (0);
}
