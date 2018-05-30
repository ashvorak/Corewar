/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:55:28 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/05/30 16:55:01 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <unistd.h>
#include "../inc/corewar.h"
#include <stdlib.h>

WINDOW	*print_data(WINDOW *stdscr, t_game *game)
{
	int i;
	int j;
	int k;

	i = 1;
	k = 0;
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	while (k < MEM_SIZE)
	{
		j = 5;
		while (k % 63 != 0)
		{
			mvprintw(i, j, game->area[k].value);
			j += 3;
			k++;
		}
		k++;
		i += 1;
	}
	attroff(COLOR_PAIR(2));
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
			mvprintw(i, 195, " ");
		}
		i++;
		usleep(50000);
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
