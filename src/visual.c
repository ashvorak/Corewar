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
/*
void    initialize_colors(void)
{
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
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

WINDOW	*print_data(WINDOW *stdscr, t_game *game)
{
	int i;
	int j;
	int k;
	int l;
	char *tmp;

	i = 2;
	k = 0;
	while (k < MEM_SIZE)
	{
		l = 0;
		j = 3;
		while (l++ < 64)
		{
			tmp = ft_itoa_base(game->area[k].value, 16);
			if (ft_strlen(tmp) == 1)
				tmp = ft_strjoin("0", tmp);
			if (game->area[k].PC == 0)
				attron(COLOR_PAIR(what_color(game->area[k].color)));
			else
				attron(COLOR_PAIR(what_color(game->area[k].color) + 5));
			mvprintw(i, j, tmp);
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

void	print_frame(WINDOW *stdscr, int speed)
{
	int i;
	int j;

	i = 0;
	attron(COLOR_PAIR(1));
	while (i < 70)
	{
		j = 0;
		if (i == 0  || i == 70 - 1 || i == 55)
		{
			while (j < 250)
			{
				if (i == 0  || i == 70 - 1 || (i == 55 && (j > 195 || j == 0)))
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
		usleep(speed);
	}
	attroff(COLOR_PAIR(1));
}

char    *prog_name(char *name)                   // фігова ідея, тому що спочатку ім'я не малочиться
{
	char *res;
	
	res = NULL;
	if (ft_strlen(name) > 38)
	{
		res = ft_strnew(39);
		ft_strncpy(res, name, 38);
		return (res);
	}
	else
		return (name);
}

void    speed(t_game *game, int y)
{
	int i;
	int j;
	int num;
	
	i = 0;
	j = 210;
	num = (-29 * game->speed / 3970) + ( 11997 / 397);
	mvprintw(y += 4, 200, "%s", "Speed:   |");
	while (i < 30)
	{
		if (i < num)
			attron(COLOR_PAIR(3));
		else
			attron(COLOR_PAIR(2));
		mvprintw(y, j++, "%s", "#");
		i++;
		if (i < num)
			attroff(COLOR_PAIR(3));
		else
			attroff(COLOR_PAIR(2));
	}
	mvprintw(y, 240, "%s", "|");
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
	if (!game->pause)
		mvprintw(3, 200, "%s", "**   RUNNING  **");
	else
		mvprintw(3, 200, "%s", "**   PAUSED   **");
	mvprintw(5, 200, "%s %d", "CYClES :", game->CYCLE);
	mvprintw(7, 200, "%s %d", "PROCESSES :", game->num_proc);
	while (i <= pn + 1)
	{
		mvprintw(y, 200, "%s %d %s", "Player", i, ":");
		attron(COLOR_PAIR(what_color(i - 1)));
		mvprintw(y, 211, prog_name(game->players[i - 1].prog_name));
		attroff(COLOR_PAIR(what_color(i - 1)));
		mvprintw(y += 2, 205, "%s %d", "Last live :              ", game->players[i - 1].last_live);
		mvprintw(y += 2, 205, "%s %d", "Lives in current period :", game->players[i - 1].lives_in_CP);
		i++;
		y += 2;
	}
	mvprintw(y + 2, 200, "%s %d", "CYCLE_TO_DIE :", game->cycle_to_die);
	mvprintw(y + 4, 200, "%s %d", "CYCLE_DELTA :", CYCLE_DELTA);
	mvprintw(y + 6, 200, "%s %d", "NBR_LIVE :", NBR_LIVE);
	mvprintw(y + 8, 200, "%s %d", "MAX_CHECKS :", MAX_CHECKS);
	speed(game, y + 8);
	mvprintw(57, 210, "HOTKEYS INFO:");
	mvprintw(59, 200, "Right ' + '   Increase speed");
	mvprintw(61, 200, "Right ' - '   Decrease speed");
	mvprintw(63, 200, "' Space '     Pause");
	mvprintw(65, 200, "' Esc '       Exit game");
	attroff(COLOR_PAIR(2));
	attroff(A_BOLD);
}

void visual(t_game *game)
{
	initialize_colors();
	print_frame(stdscr, game->speed);
	print_data(stdscr, game);
	right_menu(game);
	refresh();
}
*/