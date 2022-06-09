NAME 		=		push_swap

NAME_B		=		checker

HEAD 		=		push_swap.h

HEAD_B		=		push_swap_checker.h

SRC 		= 		push_swap.c			push_swap_game.c	push_swap_med.c			push_swap_sort.c \
					push_swap_ops_1.c	push_swap_ops_2.c	push_swap_start_game.c	

SRC_B 		= 		push_swap_ops_1.c	push_swap_ops_2.c		push_swap_checker.c

OBJ 		=		$(SRC:%.c=%.o)

OBJ_B		=		$(SRC_B:%.c=%.o)

D 			=		$(SRC:%.c=%.d)

D_B 		=		$(SRC_B:%.c=%.d)

CFLAGS 		= 		-Wall -Werror -Wextra -MD

CC 			= 		gcc

RM 			= 		rm -f

all 		: 		$(NAME)


$(NAME) 	: 		$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) -o $@

%.o 		: 		%.c
					$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

include 			$(wildcard $(D) $(D_B))

bonus		:		
					@make OBJ="$(OBJ_B)" HEAD="$(HEAD_B)" NAME="$(NAME_B)" all

clean		:
					@$(RM) $(OBJ) $(D) $(OBJ_B) $(D_B) 

fclean		: 		clean
					@$(RM) $(NAME) $(NAME_B)

re			: 		fclean all

.PHONY		: 		all clean fclean re bonus
