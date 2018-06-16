/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:06:17 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/12 18:06:18 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	initialize_colors(void)
{
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_GREY);
	init_pair(2, COLOR_GREY, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_GREY);
	init_pair(8, COLOR_BLACK, COLOR_GREEN);
	init_pair(9, COLOR_BLACK, COLOR_BLUE);
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(12, COLOR_WHITE, COLOR_BLACK);
}

int		what_color(int col)
{
	if (col == 0)
		return (3);
	else if (col == 1)
		return (4);
	else if (col == 2)
		return (5);
	else if (col == 3)
		return (6);
	else
		return (2);
}

void	switcher(t_game *game, int k, int flag)
{
	if (flag == 1)
	{
		if (game->area[k].bold > 0)
			attron(A_BOLD);
		if (game->area[k].pc == 0)
			attron(COLOR_PAIR(what_color(game->area[k].color)));
		else
			attron(COLOR_PAIR(what_color(game->area[k].color) + 5));
	}
	if (flag == 2)
	{
		if (game->area[k].pc == 0)
			attroff(COLOR_PAIR(what_color(game->area[k].color)));
		else
			attroff(COLOR_PAIR(what_color(game->area[k].color) + 5));
		if (game->area[k].bold > 0)
		{
			attroff(A_BOLD);
			game->area[k].bold--;
		}
	}
}

void	print_data(t_game *game)
{
	int		i;
	int		j;
	int		k;
	int		l;

	i = 2;
	k = 0;
	while (k < MEM_SIZE)
	{
		l = 0;
		j = 3;
		while (l++ < 64)
		{
			switcher(game, k, 1);
			mvprintw(i, j, "%.2x", game->area[k].value);
			j += 3;
			switcher(game, k++, 2);
		}
		i++;
	}
}

void	print_frame(WINDOW *stdscr, int speed)
{
	int i;
	int j;

	i = -1;
	attron(COLOR_PAIR(1));
	while (++i < 70)
	{
		j = -1;
		if (i == 0 || i == 70 - 1 || i == 55)
		{
			while (++j < 250)
			{
				if (i == 0 || i == 70 - 1 || (i == 55 && (j > 195 || j == 0)))
					mvprintw(i, j, " ");
			}
		}
		else
		{
			mvprintw(i, ++j, " ");
			mvprintw(i, 250 - 1, " ");
			mvprintw(i, 196, " ");
		}
		usleep(speed);
	}
	attroff(COLOR_PAIR(1));
}
