# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/23 11:59:18 by oshvorak          #+#    #+#              #
#    Updated: 2018/06/09 18:28:31 by oshvorak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC =	./src/main.c \
		./src/read_player.c \
		./src/read_players.c \
		./src/fill_area.c \
		./src/visual.c \
		./src/visual_2.c \
		./src/visual_3.c \
		./src/start_game.c \
		./src/start_game_2.c \
		./src/check_codage.c \
		./src/op_aff.c \
		./src/op_zjmp.c \
		./src/op_sti.c \
		./src/op_st.c \
		./src/write_2_4_bytes.c \
	    ./src/op_live.c \
	    ./src/op_and.c \
	    ./src/op_fork.c \
        ./src/op_lfork.c \
        ./src/op_or.c \
        ./src/op_xor.c \
		./src/op_ld.c \
		./src/op_add.c \
		./src/op_ldi.c \
		./src/op_lld.c \
		./src/op_lldi.c \
		./src/op_sub.c \
		./src/jump_pc.c \
		./src/flags_read.c \
		./src/dump.c \
		./src/finish_game.c \
		./src/execute_process.c

MLIB = make -C lib

LIB = lib/libftprintf.a

OBJS =	$(SRC:.c=.o)

all: $(NAME)

$(NAME): color $(OBJS)
	@echo " 100%\n"
	@echo "\033[0;37mMake library\033[0;32m"
	@$(MLIB) 
	@gcc -lncurses -Wall -Wextra -Werror $(OBJS) $(LIB) -o $(NAME)
	@echo "\033[0;37mComplite"
	
color:
	@echo "Make program corewar\033[0;32m"

.c.o:
		@echo -n '█'
		@$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	@$(MLIB) clean
	@/bin/rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@$(MLIB) fclean

re: fclean all