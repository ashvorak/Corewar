/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:45:31 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/12 18:45:32 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int				push_op_id(unsigned char value)
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

static	void	execute_add(t_game *game, t_process *process)
{
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
		process->op_id = push_op_id(game->area[process->PC].value);
		game->area[process->PC].PC = 1;
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
			game->area[tmp->PC].PC = 0;
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
			game->players[tmp->color].count_lives += tmp->live;
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
	while (i < game->players_num)
	{
		if (game->players[i].count_lives > 21 || game->checks == MAX_CHECKS)
		{
			game->cycle_to_die -= CYCLE_DELTA;
			game->checks = 0;
		}
		i++;
	}
	i = 0;
	while (i < game->players_num)
		game->players[i++].count_lives = 0;
	return (0);
}