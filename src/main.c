/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 16:26:00 by oshvorak          #+#    #+#             */
/*   Updated: 2018/05/31 18:55:06 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	ft_error(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (!(game = (t_game*)malloc(sizeof(t_game))))
		return (0);
	read_players(game, av, ac, 1);
	fill_area(game);
	visual(game);
	return (0);
}