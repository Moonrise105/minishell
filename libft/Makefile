# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olydden <olydden@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/30 16:02:34 by olydden           #+#    #+#              #
#    Updated: 2021/03/06 16:45:53 by olydden          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

FLAGS = -O3 -g -Wall -Wextra -Werror

DIR_S = srcs

DIR_O = obj

HEADER = includes

SOURCES = 	ft_memset.c\
			ft_bzero.c\
			ft_memcpy.c\
			ft_memccpy.c\
			ft_memmove.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_strlen.c\
			ft_strlcpy.c\
			ft_strlcat.c\
			ft_strchr.c\
			ft_strrchr.c\
			ft_strnstr.c\
			ft_strncmp.c\
			ft_atoi.c\
			ft_isalpha.c\
			ft_isdigit.c\
			ft_isalnum.c\
			ft_isascii.c\
			ft_isprint.c\
			ft_toupper.c\
			ft_tolower.c\
			ft_calloc.c\
			ft_strdup.c\
			ft_substr.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_split.c\
			ft_itoa.c\
			ft_strmapi.c\
			ft_putchar.c\
			ft_putchar_fd.c\
			ft_putstr.c\
			ft_putstr_fd.c\
			ft_putendl.c\
			ft_putnbr.c\
			ft_strndup.c\
			ft_free.c\
			ft_itoa_base.c\
			ft_nbrlen.c\
			ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c\
			ft_nbrlen_u.c\
			ft_putnbr_u.c\
			ft_itoa_base_upper.c\
			ft_strcmp.c\
			ft_strncmp_end.c\
			ft_strnew.c\
			ft_lstindex.c\
			ft_atoi_orig.c\
			get_next_line.c\
			ft_printf/ft_printf.c\
			ft_printf/s_specifier.c\
			ft_printf/d_d4_specifier.c\
			ft_printf/d5_d9_specifier.c\
			ft_printf/d10_d14_specifier.c\
			ft_printf/d15_d16_specifiers.c\
			ft_printf/u_u4_specifier.c\
			ft_printf/u5_u7_c_percent_specifiers.c\
			ft_printf/x_x4_specifier.c\
			ft_printf/x5_x8_specifier.c\
			ft_printf/p_specifier.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/libft.h
	@mkdir -p obj obj/ft_printf
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re