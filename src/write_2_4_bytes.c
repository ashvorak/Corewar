/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_2_4_bytes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:54:13 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/06/13 14:54:45 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

unsigned int	write_2_bytes(t_game *game, int pc)
{
	unsigned int arg;

	arg = game->area[(pc) % MEM_SIZE].value << 8;
	arg = arg | game->area[(pc + 1) % MEM_SIZE].value;
	return (arg);
}

unsigned int	write_4_bytes(t_game *game, int pc)
{
	unsigned int arg;

	arg = game->area[(pc) % MEM_SIZE].value << 24;
	arg = arg | (game->area[(pc + 1) % MEM_SIZE].value << 16);
	arg = arg | (game->area[(pc + 2) % MEM_SIZE].value << 8);
	arg = arg | game->area[(pc + 3) % MEM_SIZE].value;
	return (arg);
}
