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

NAME =	asm

CC =	gcc

FLAGS =	-Wall -Werror -Wextra

SRC =	ft_2bin.o ft_add_basic.o ft_add_num.o ft_addit_func.o ft_bin_struct.o \
        ft_del.o ft_find_args_type.o ft_find_len2link.o ft_goto.o ft_new.o \
        ft_opcode.o ft_output.o ft_read_all.o ft_read_code.o ft_read_key.o \
        ft_read_label.o ft_read_name_comm.o ft_valid.o main.o op.o

MLIB =	make -C libftprintf

LIB =	libftprintf/libftprintf.a

OBJS =	$(SRC:.c=.o)

all: $(NAME)

$(NAME): color $(OBJS)
		@echo " 100%\n"
		@echo "\033[0;37mMake library\033[0;32m"
		@$(MLIB)
		@$(CC) $(FLAGS) $(OBJS) $(LIB) -o $(NAME)
		@echo "\033[0;37mComplite"

.c.o:
		@echo -n '█'
		@$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

color:
	@echo "Make program asm\033[0;32m"

clean:
	@rm -f $(OBJS)
	@$(MLIB) clean

fclean: clean
	@rm -f $(NAME)
	@$(MLIB) fclean

re: fclean all
