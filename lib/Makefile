# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/25 12:30:49 by oshvorak          #+#    #+#              #
#    Updated: 2018/04/11 16:28:30 by oshvorak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FT_PRINTF = ./ft_printf/src/active_bits.c \
			./ft_printf/src/convert_base.c \
			./ft_printf/src/convert_int.c \
			./ft_printf/src/convert_float.c \
			./ft_printf/src/ft_printf.c \
			./ft_printf/src/ft_putwchar.c \
			./ft_printf/src/handle_char.c \
			./ft_printf/src/handle_n.c \
			./ft_printf/src/handle_num.c \
			./ft_printf/src/handle_float.c \
			./ft_printf/src/handle_str.c \
			./ft_printf/src/handle_qualifier.c \
			./ft_printf/src/handle_value.c \
			./ft_printf/src/handle_wchar.c \
			./ft_printf/src/handle_wstr.c \
			./ft_printf/src/is_type.c \
			./ft_printf/src/ft_realloc.c \
			./ft_printf/src/make_colors.c \
			./ft_printf/src/size_char.c

GNL = ./get_next_line/get_next_line.c

LIBFT = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c \
		ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c \
		ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
		ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
		ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
		ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
		ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
		ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c \
		ft_swap.c ft_sqrt.c ft_strcapitalize.c ft_factorial.c ft_listsize.c ft_charreplace.c \
		ft_atoi_base.c ft_free_arr.c ft_array_size.c ft_free_arr_int.c ft_itoa_base.c

LIBFT_OBJ = $(LIBFT:.c=.o)

FT_PRINTF_OBJ = $(FT_PRINTF:.c=.o)

GNL_OBJ = $(GNL:.c=.o)

all: $(NAME)

$(NAME): $(FT_PRINTF_OBJ) $(LIBFT_OBJ) $(GNL_OBJ)
	ar rc $(NAME) $(FT_PRINTF_OBJ) $(LIBFT_OBJ) $(GNL_OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(FT_PRINTF_OBJ) $(LIBFT_OBJ) $(GNL_OBJ)

fclean:	clean
	/bin/rm -f $(NAME)

re: fclean all
