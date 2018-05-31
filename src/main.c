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

int	main(int ac, char **av)
{
 	int		i;
	unsigned int		j;
	t_game	*game;

	if (!(game = (t_game*)malloc(sizeof(t_game))))
		return (0);
	read_players(game, av, ac, 1);
	i = 0;
	j = 0;
	while (i < MEM_SIZE)
	{
		//game->area[i].value = j < game->players[0].prog_size ? game->players[0].opcode[j] : ft_strdup("00");
		if (j < game->players[0].prog_size)
		{
			game->area[i].value = game->players[0].opcode[j];
			game->area[i].color = 0;
		}
		else
		{
			game->area[i].value = ft_strdup("00");
			game->area[i].color = 10;
		}
		i++;
		j++;
	}
	
	// i = 0;
	// j = 0;
	// while (game->area[i].value)
	// 	i++;
	// ft_printf("%d\n", i);
	/*
	while (i < 100)
	{
		ft_printf("%s\n", game->area[i].value);
		i++;
	}
	*/	
	visual(game);
	return (0);
}