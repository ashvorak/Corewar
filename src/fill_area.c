/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_area.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 18:37:49 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/04 11:20:49 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

int				players_num(t_game *game)
{
	int i;

	i = 0;
	while (game->players[i].prog_size)
		i++;
	return (i - 1);
}

static	void	fill_reg(t_process *process)
{
	int i;

	i = 0;
	while (i < 16)
	{
		process->REG_NUM[i] = 0;
		i++;
	}
}

void			push_procces(t_game *game, int location, unsigned int reg1)
{
	t_process *tmp;
	t_process *process;

	if (!(process = (t_process*)malloc(sizeof(t_process))))
		exit(1);
	fill_reg(process);
	process->REG_NUM[0] = reg1;
	process->PC = location;
	process->live = 0;
	process->op_id = 16;
	process->CYCLE_TO_DONE = 1;
	process->carry = 0;
	process->num = 1;
	process->next = NULL;
	process->prev = NULL;
	if (game->process)
	{
		tmp = game->process;
		process->next = tmp;
		tmp->prev = process;
		game->process = process;
	}
	else
		game->process = process;
}

static	void	fill_players(t_game *game)
{
	int				i;
	int				j;
	int				n;
	int				pn;
	unsigned int	reg1;

	i = -1;
	n = -1;
	reg1 = 4294967295;
	pn = players_num(game);
	while (++i < MEM_SIZE)
	{
		j = 0;
		if (++n <= pn)
		{
			i = (0 + (MEM_SIZE / (pn + 1))) * n;
			push_procces(game, i, reg1--);
			while (j < (int)game->players[n].prog_size)
			{
				game->area[i].value = game->players[n].opcode[j++];
				game->area[i].color = n;
				game->area[i++].player = 1;
			}
		}
	}
}

void			fill_area(t_game *game)
{
	int	i;

	i = 0;
	fill_players(game);
	while (i < MEM_SIZE)
	{
		if (!game->area[i].player)
		{
			game->area[i].value = 0;
			game->area[i].color = 10;
		}
		i++;
	}
}
