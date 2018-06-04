/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:55:28 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/05/31 18:41:53 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

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

WINDOW	*print_data(WINDOW *stdscr, t_game *game)
{
	int i;
	int j;
	int k;
	int l;

	i = 2;
	k = 0;
	//start_color();
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_WHITE);
	init_pair(8, COLOR_GREEN, COLOR_WHITE);
	init_pair(9, COLOR_BLUE, COLOR_WHITE);
	init_pair(10, COLOR_RED, COLOR_WHITE);
	init_pair(11, COLOR_YELLOW, COLOR_WHITE);
	//game->area[0].karetka = 1;    // test of PC //// delete it
	while (k < MEM_SIZE)
	{
		l = 0;
		j = 3;
		while (l++ < 64)
		{
			if (game->area[k].karetka == 0)
				attron(COLOR_PAIR(what_color(game->area[k].color)));
			else
				attron(COLOR_PAIR(what_color(game->area[k].color) + 5));
			mvprintw(i, j, game->area[k].value);
			j += 3;
			if (game->area[k].karetka == 0)
				attroff(COLOR_PAIR(what_color(game->area[k].color)));
			else
				attroff(COLOR_PAIR(what_color(game->area[k].color) + 5));
			k++;
		}
		i++;
	}
	return (stdscr);
}

void	print_frame(WINDOW *stdscr)
{
	int i;
	int j;

	i = 0;
	start_color();
	//wattron(stdscr, COLOR_PAIR(2));
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	attron(COLOR_PAIR(1));
	while (i < 70)
	{
		j = 0;
		if (i == 0  || i == 70 - 1)
		{
			while (j < 250)
			{
				mvprintw(i, j, " ");
				j++;
			}
		}
		else
		{
			mvprintw(i, j, " ");
			mvprintw(i, 250 - 1, " ");
			mvprintw(i, 196, " ");
		}
		i++;
		usleep(2000);
	}
	attroff(COLOR_PAIR(1));
}

void	right_menu(t_game *game)
{
	int pn;
	int i;
	int y;

 	i = 1;
	y = 10;
	pn = players_num(game);
	if (pn < 0)
		ft_error();
	attron(A_BOLD);
	attron(COLOR_PAIR(2));
	mvprintw(5, 200, "%s %d", "CYClES :", game->CYCLE);

	mvprintw(7, 200, "PROCESSES :");

	while (i <= pn + 1)
	{
		mvprintw(y, 200, "%s %d %s", "Player", i, ":");
		attron(COLOR_PAIR(what_color(i - 1)));
		mvprintw(y, 211, game->players[i - 1].prog_name);
		attroff(COLOR_PAIR(what_color(i - 1)));
		i++;
		y += 2;
	}
	mvprintw(y + 2, 200, "CYCLE_TO_DIE :");

	mvprintw(y + 4, 200, "CYCLE_DELTA :");

	mvprintw(y + 6, 200, "NBR_LIVE :");

	mvprintw(y + 8, 200, "MAX_CHECKS :");


	attroff(COLOR_PAIR(2));
	attroff(A_BOLD);
}

void visual(t_game *game)
{
	print_frame(stdscr);
	print_data(stdscr, game);
	right_menu(game);
	refresh();
	//getch();    // wait for space or may be other button
}