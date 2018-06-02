# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/23 11:59:18 by oshvorak          #+#    #+#              #
#    Updated: 2018/06/01 14:10:23 by oshvorak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC =	./src/main.c \
		./src/read_player.c \
		./src/read_players.c \
		./src/fill_area.c \
		./src/visual.c

MLIB = make -C lib

LIB = lib/libftprintf.a

all: $(NAME)

$(NAME): $(SRC)
	$(MLIB) 
	gcc -lncurses -Wall -Wextra -Werror $(SRC) $(LIB) -o $(NAME)
	
clean:
	$(MLIB) clean

fclean: clean
	rm -f $(NAME)
	$(MLIB) fclean

re: fclean all