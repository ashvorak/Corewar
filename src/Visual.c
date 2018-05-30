/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:55:28 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/05/24 15:55:29 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <unistd.h>
#include "../inc/corewar.h"
#include <stdlib.h>

typedef	struct	s_gen
{
	t_sector	array[MEM_SIZE];
}				t_gen;


void	create_array(t_gen *st)
{
	int			i;

	i = 0;
	while (i < MEM_SIZE)
	{
		st->array[i].value = ft_strdup("00");
		st->array[i].color = 0;
		st->array[i].pc = 0;
		i++;
	}
}

WINDOW	*print_data(WINDOW *stdscr, t_gen *st)
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
			mvprintw(i, j, st->array[k].value);
			j += 3;
			k++;
		}
		k++;
		i += 1;
	}
	attroff(COLOR_PAIR(2));
	return (stdscr);
}

void	print_frame(WINDOW *stdscr, t_gen *st)
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
	t_gen	st;

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
	create_array(&st);
	while (1)
	{
		clear();
		getmaxyx(stdscr, max_y, max_x);
		print_frame(stdscr, &st);
		stdscr = print_data(stdscr, &st);
		refresh();
	}
	getch();
	endwin();
}
