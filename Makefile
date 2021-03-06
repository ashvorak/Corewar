# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amazurok <amazurok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 16:40:55 by amazurok          #+#    #+#              #
#    Updated: 2018/06/09 16:05:19 by amazurok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = asm

NAME2 = corewar

MASM =	make -C assembler

MCOR =	make -C vm

all:
	@$(MASM)
	@echo ""
	@$(MCOR)
	@mv ./assembler/$(NAME1) .
	@mv ./vm/$(NAME2) .

clean:
	@$(MASM) clean
	@$(MCOR) clean

fclean: clean
	@rm -f asm
	@rm -f corewar
	@$(MASM) fclean
	@$(MCOR) fclean

re: fclean all
