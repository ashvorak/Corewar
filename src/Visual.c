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

#include <ncurses.h>
#include <unistd.h>
#include "../inc/corewar_vm.h"
#include <stdlib.h>

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
	start_color();
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
	game->area[0].PC = 1;
	while (k < MEM_SIZE)
	{
		l = 0;
		j = 3;
		while (l++ < 64)
		{
			if (game->area[k].PC == 0)
				attron(COLOR_PAIR(what_color(game->area[k].color)));
			else
				attron(COLOR_PAIR(what_color(game->area[k].color) + 5));
			mvprintw(i, j, game->area[k].value);
			j += 3;
			if (game->area[k].PC == 0)
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
	wattron(stdscr, COLOR_PAIR(2));
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
		usleep(10000);
	}
	attroff(COLOR_PAIR(1));
}

void visual(t_game *game)
{
	int x;
	int y;
	int max_x;
	int max_y;
	int next_x;
	int direction;

	x = 0;
	y = 0;
	max_x = 0;
	max_y = 0;
	next_x = 0;
	direction = 1;
	initscr();
	//cbreak();
	noecho();
	curs_set(FALSE);
	while (1)
	{
		clear();
		getmaxyx(stdscr, max_y, max_x);
		print_frame(stdscr);
		stdscr = print_data(stdscr, game);
		refresh();
	}
	getch();
	endwin();
}
