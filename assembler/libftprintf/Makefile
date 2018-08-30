# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amazurok <amazurok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/15 16:13:47 by amazurok          #+#    #+#              #
#    Updated: 2018/05/12 12:10:59 by amazurok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libftprintf.a

CC =				gcc

FLAGS =				-Wall -Werror -Wextra

LIB_DIR = ./libft

PRF_DIR = ./ft_printf

LIB_SRC = 	ft_atoi.o ft_bzero.o ft_char_replace.o ft_isalnum.o ft_isalpha.o \
			ft_isascii.o ft_isdigit.o ft_isprint.o ft_itoa.o ft_lstadd.o \
			ft_lstadd_end.o ft_lstdel.o ft_lstdelone.o ft_lstiter.o ft_lstlen.o \
			ft_lstmap.o ft_lstnew.o ft_memalloc.o ft_memccpy.o ft_memchr.o \
			ft_memcmp.o ft_memcpy.o ft_memdel.o ft_memmove.o ft_memset.o \
			ft_putchar.o ft_putchar_fd.o ft_putendl.o ft_putendl_fd.o ft_putnbr.o \
			ft_putnbr_fd.o ft_putstr.o ft_putstr_fd.o ft_strcat.o ft_strchr.o \
			ft_strclr.o ft_strcmp.o ft_strcpy.o ft_strdel.o ft_strdup.o ft_strequ.o \
			ft_striter.o ft_striteri.o ft_strjoin.o ft_strlcat.o ft_strlen.o \
			ft_strmap.o ft_strmapi.o ft_strncat.o ft_strncmp.o ft_strncpy.o \
			ft_strnequ.o ft_strnew.o ft_strnstr.o ft_strrchr.o ft_strsplit.o \
			ft_strstr.o ft_strsub.o ft_strtrim.o ft_tolower.o ft_toupper.o \
			ft_realloc.o get_next_line.o ft_dstrdel.o ft_intrealloc.o ft_realcat.o\
			ft_set_val.o

PRF_SRC = 	ft_addchar.o ft_check_key.o ft_del_key.o ft_itoa_base.o ft_myputustr_fd.o \
			ft_n.o ft_new_list.o ft_nonoercent.o ft_print_char_str.o \
			ft_print_digit.o ft_print_float.o ft_print_res.o ft_print_unicode.o \
			ft_print_w_char.o ft_printf.o ft_processing_args.o ft_putuchar_fd.o \
			ft_search_in_line.o ft_size2dig.o ft_strtounicat.o \
			ft_strupper.o ft_wrealloc.o ft_wstrdel.o ft_wstrlen.o ft_wstrzero.o

COMPILED =	$(LIB_SRC) $(PRF_SRC)

all: $(NAME)

$(NAME): $(COMPILED)
	@ar rc $(NAME) $(COMPILED)
	@ranlib $(NAME)
	@echo " 100%\n"

$(LIB_SRC): %.o: $(LIB_DIR)/%.c
	@echo -n '█'
	@$(CC) -c $(FLAGS) -I $(LIB_DIR) $< -o $@

$(PRF_SRC): %.o: $(PRF_DIR)/%.c
	@echo -n '█'
	@$(CC) -c $(FLAGS) -I $(PRF_DIR) $< -o $@

clean:
	@-/bin/rm -f $(COMPILED)

fclean: clean
	@-/bin/rm -f $(NAME)

re: fclean all
