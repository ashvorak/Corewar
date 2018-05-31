/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:26:00 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/30 17:00:46 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	ft_error(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

int	players_num(t_game *game)
{
	int i;

	i = 0;
	while (game->players[i].prog_size)
		i++;
	return (i - 1);
}

int	main(int ac, char **av)
{
 	int		i;
	unsigned int		j;
	t_game	*game;
	int		pn;
	int		n;

	if (!(game = (t_game*)malloc(sizeof(t_game))))
		return (0);
	read_players(game, av, ac, 1);
	pn = players_num(game);
	i = 0;
	j = 0;
	n = 0;
	while (i < MEM_SIZE)
	{
		j = 0;
		if (n <= pn)
		{
			i = (0 + (MEM_SIZE / (pn + 1))) * n;
			while (j < game->players[n].prog_size)
			{
				game->area[i].value = game->players[n].opcode[j];
				game->area[i].color = n;
				j++;
				i++;
			}
			n++;
		}
		i++;
	}
	i = 0;
	while (i < MEM_SIZE)
	{
		if (!game->area[i].value)
		{
			game->area[i].value = ft_strdup("00");
			game->area[i].color = 10;
		}
		i++;
	}
	visual(game);
	return (0);
}