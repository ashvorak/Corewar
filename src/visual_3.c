/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 18:08:02 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/12 18:08:03 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

char	*prog_name(char *name)
{
	if (ft_strlen(name) > 38)
	{
		name[38] = '\0';
		return (name);
	}
	else
		return (name);
}

void	speed(t_game *game, int y)
{
	int i;
	int j;
	int num;

	i = 0;
	j = 210;
	num = (-29 * game->speed / 3970) + (11997 / 397);
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

int		print_players(t_game *game, int pn, int y)
{
	int i;

	i = 1;
	while (i <= pn + 1)
	{
		mvprintw(y, 200, "%s %d %s", "Player",
			(int)get_first_reg(game->players[i - 1].n, game, i - i), ":");
		attron(COLOR_PAIR(what_color(i - 1)));
		mvprintw(y, 211, prog_name(game->players[i - 1].prog_name));
		attroff(COLOR_PAIR(what_color(i - 1)));
		mvprintw(y += 2, 205, "%s %d", "Last live :              ",
			game->players[i - 1].last_live);
		mvprintw(y += 2, 205, "%s %d", "Lives in current period :",
			game->players[i - 1].lives_in_cp);
		i++;
		y += 2;
	}
	return (y);
}

void	print_info(t_game *game, int y)
{
	mvprintw(y + 2, 200, "%s %d", "CYCLE_TO_DIE :", game->cycle_to_die);
	mvprintw(y + 4, 200, "%s %d", "CYCLE_DELTA :", CYCLE_DELTA);
	mvprintw(y + 6, 200, "%s %d", "NBR_LIVE :", NBR_LIVE);
	mvprintw(y + 8, 200, "%s %d", "MAX_CHECKS :", MAX_CHECKS);
	speed(game, y + 8);
	if (game->finish)
	{
		attron(COLOR_PAIR(what_color(game->winner)));
		mvprintw(y + 16, 200, "The winner is : %s",
		         game->players[game->winner].prog_name);
		attroff(COLOR_PAIR(what_color(game->winner)));
	}
	mvprintw(57, 210, "HOTKEYS INFO:");
	mvprintw(59, 200, "Right ' + '   Increase speed");
	mvprintw(61, 200, "Right ' - '   Decrease speed");
	mvprintw(63, 200, "' Space '     Pause");
	mvprintw(65, 200, "' Esc '       Exit game");
}

void	right_menu(t_game *game)
{
	int pn;
	int y;

	y = 10;
	pn = players_num(game);
	if (pn < 0)
		ft_error("No players", game);
	attron(A_BOLD);
	attron(COLOR_PAIR(12));
	if (!game->pause)
		mvprintw(3, 200, "%s", "**   RUNNING  **");
	else
		mvprintw(3, 200, "%s", "**   PAUSED   **");
	mvprintw(5, 200, "%s %d", "CYClES :", game->cycle);
	mvprintw(7, 200, "%s %d", "PROCESSES :", game->num_proc);
	y = print_players(game, pn, y);
	print_info(game, y);
	attroff(COLOR_PAIR(12));
	attroff(A_BOLD);
}
