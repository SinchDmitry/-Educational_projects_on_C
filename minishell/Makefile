NAME 	=		minishell

HEAD 	=		minishell.h

SRC 	= 		minishell.c			pre_parser.c		pre_arguments.c		\
				pre_command.c		pre_redirect.c		pre_utils.c			\
				gen_parser.c		gen_utils.c			gen_checker.c		\
				gen_free.c			gen_wildcard.c		gen_signal.c		\
				pre_check.c			gen_env.c			\
				build/build.c		build/exp_utils.c	build/unset.c		\
				build/free.c		build/path.c		build/red.c			\
				build/pipe.c		build/red_2.c		build/system.c		\
				build/cd.c			build/echo.c		build/env.c			\
				build/pwd.c			build/export.c		build/export_2.c

OBJ 	=		$(SRC:%.c=%.o)

D 		=		$(SRC:%.c=%.d)


LIBDIR	= 		./libft/

LIBFT	= 		libft.a

CFLAGS 	= 		-Wall -Werror -Wextra -MD -g

CC 		= 		cc

RM 		= 		rm -f

all 		: 		libmake $(NAME)

$(NAME) 	: 		$(OBJ)
					@cp $(LIBDIR)$(LIBFT) .
					$(CC) $(CFLAGS) $(OBJ) libft.a -o $@ -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
 
libmake 	:			
					@make -C $(LIBDIR)

%.o 		: 		%.c
					$(CC) $(CFLAGS) -c $< -o $@ -I /Users/$(USER)/.brew/opt/readline/include

include 			$(wildcard $(D))

clean		:
					@$(RM) $(OBJ) $(D) 

fclean		: 		clean
					@$(RM) $(NAME) $(LIBFT)
					@make fclean -C $(LIBDIR)

re			: 		fclean all

.PHONY		: 		all clean fclean re bonus
