/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_2_4_bytes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:54:13 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/12 17:54:15 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

unsigned int	write_2_bytes(t_game *game, int pc)
{
	unsigned int arg;

	arg = game->area[pc].value << 8;
	arg = arg | game->area[pc + 1].value;
	return (arg);
}

unsigned int	write_4_bytes(t_game *game, int pc)
{
	unsigned int arg;

	arg = game->area[pc].value << 24;
	arg = arg | (game->area[pc + 1].value << 16);
	arg = arg | (game->area[pc + 2].value << 8);
	arg = arg | game->area[pc + 3].value;
	return (arg);
}
