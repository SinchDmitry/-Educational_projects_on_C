NAME 		=		philo

HEAD 		=		philo.h

SRC 		= 		philo.c		philo_utils.c	philo_func.c 

OBJ 		=		$(SRC:%.c=%.o)

D 			=		$(SRC:%.c=%.d)

CFLAGS 		= 		-Wall -Werror -Wextra -MD 
# -fsanitize=address

CC 			= 		gcc

RM 			= 		rm -f

all 		: 		$(NAME)

$(NAME) 	: 		$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) -o $@

%.o 		: 		%.c
					$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

include 			$(wildcard $(D))

clean		:
					@$(RM) $(OBJ) $(D) 

fclean		: 		clean
					@$(RM) $(NAME) 

re			: 		fclean all

.PHONY		: 		all clean fclean re bonus
