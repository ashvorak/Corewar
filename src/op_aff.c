/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:47:38 by oshvorak          #+#    #+#             */
/*   Updated: 2018/06/02 15:10:06 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar_vm.h"

void	op_aff(t_game *game, t_process *process)
{
	int t_reg;

	t_reg = 0;
	if (!check_codege(process->op_id, ft_atoi_base(game->area[process->PC + 1].value, 16)))
		return ;
	t_reg = ft_atoi_base(game->area[process->PC + 2].value, 16);
	ft_printf("%c\n", t_reg % 256);
}
