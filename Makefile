NAME = minishell

CC = gcc

HEADER = includes

FLAGS_C = -g3
# -Wall -Wextra -Werror 

DIR_LIBFT = libft

DIR_S = srcs_new

DIR_O = objs

SOURCES =	dict.c \
			main.c \
			parser/parser.c \
			parser/add_parser.c \
			parser/check_parser.c \
			parser/free_parser.c \
			parser/utils/utils_00_parser.c \
			parser/utils/utils_01_parser.c \
			parser/arg_parser/arg_parser.c\
			parser/arg_parser/utils_00_arg_parser.c \
			manager.c \
			execute.c \
			jmp_handlers.c \
			echo.c \
			messages.c \
			signals.c \
			finder.c \
			env.c \
			pipes.c \
			utils_00.c \
			redirects.c \
			dirs.c \

SRCS = $(addprefix $(DIR_S)/, $(SOURCES))

OBJS = $(addprefix $(DIR_O)/, $(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(DIR_LIBFT) -j 4
	@$(CC) -o $@ $^ $(DIR_LIBFT)/libft.a -ltermcap

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER)/minishell_new.h
	@mkdir -p $(DIR_O) $(DIR_O)/parser $(DIR_O)/parser/utils $(DIR_O)/parser/arg_parser
	@$(CC) $(FLAGS_C) -I $(HEADER) -c $< -o $@

clean:
	@rm -rf $(DIR_O)
	@make clean -C $(DIR_LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(DIR_LIBFT)

re: fclean all

.PHONY: fclean re all clean
