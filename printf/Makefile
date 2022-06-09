NAME =	libftprintf.a

HEAD = ft_printf.h

HEADER_BONUS = ft_printf_bonus.h

LIBDIR = ./libft/

LIBFT = libft.a

SRC_FILES = ft_printf.c	ft_printf_utils.c	ft_writer.c

SRC_BONUS_FILES =	ft_printf_bonus.c	ft_printf_utils_char_bonus.c \
ft_printf_utils_flag_bonus.c	ft_printf_utils_hex_bonus.c \
ft_printf_utils_numeric_bonus.c 

OBJ = $(patsubst %.c,%.o,$(SRC_FILES))

OBJ_B = $(patsubst %.c,%.o,$(SRC_BONUS_FILES))

D_FILES = $(patsubst %.c,%.d,$(SRC_FILES))

D_FILES_B = $(patsubst %.c,%.d,$(SRC_BONUS_FILES))

CFLAGS = -Wall -Werror -Wextra -MD -I./libft/

CC = gcc

RM = rm -f

all : $(NAME)

$(NAME) : $(OBJ) 
	make -C $(LIBDIR)
	cp $(LIBDIR)$(LIBFT) ./$(NAME)
	ar -rcs $(NAME) $(OBJ) $(HEAD)

%.o : %.c
	$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

include $(wildcard $(D_FILES) $(D_FILES_B))

bonus:
	@make SRC_FILES="$(SRC_BONUS_FILES)" HEAD="$(HEADER_BONUS)" all

clean:
	@make clean -C $(LIBDIR)
	$(RM) $(OBJ) $(OBJ_B) $(D_FILES) $(D_FILES_B)

fclean: clean
	@make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus