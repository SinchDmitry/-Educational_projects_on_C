NAME_C =		client

NAME_S =		server

HEADER =		minitalk.h

HEADER_BONUS =	minitalk_bonus.h

PRINTF = 		ft_printf.c				ft_printf_utils.c

PRINTF_BONUS =	ft_printf_bonus.c		ft_printf_utils_bonus.c

SRC_C = 		$(PRINTF)				minitalk_client.c 				

SRC_S =			$(PRINTF)				minitalk_server.c

SRC_BONUS_C =	$(PRINTF_BONUS)			minitalk_client_bonus.c

SRC_BONUS_S =	$(PRINTF_BONUS)			minitalk_server_bonus.c	

OBJ_C =			$(patsubst %.c,%.o,$(SRC_C))

OBJ_S =			$(patsubst %.c,%.o,$(SRC_S))

OBJ_BONUS_C =	$(patsubst %.c,%.o,$(SRC_BONUS_C))

OBJ_BONUS_S =	$(patsubst %.c,%.o,$(SRC_BONUS_S))

D_C =			$(patsubst %.c,%.d,$(SRC_C))

D_S =			$(patsubst %.c,%.d,$(SRC_S))

D_BONUS_C =		$(patsubst %.c,%.d,$(SRC_BONUS_C))

D_BONUS_S =		$(patsubst %.c,%.d,$(SRC_BONUS_S))

CFLAGS = 		-Wall -Werror -Wextra -MD 

CC = 			gcc

RM = 			rm -f

all : 			$(NAME_C) $(NAME_S)

$(NAME_C) : 	$(OBJ_C)
				@printf "\n\033[1;33m ⏳ chill out and wait ⏳\033[0m\n\n"
				@$(CC) $(CFLAGS) $? -o $@
				@printf "\033[1;32m 💌 $@ is done, enjoy it 👻\033[0m\n\n"

$(NAME_S) : 	$(OBJ_S)
				@printf "\n\033[1;33m ⏳ chill out and wait ⏳\033[0m\n\n"
				@$(CC) $(CFLAGS) $? -o $@
				@printf "\033[1;32m 👀 $@ is done, enjoy it 👻\033[0m\n\n"

%.o : 			%.c 
				@$(CC) $(CFLAGS) -c $< -o $@

include 		$(wildcard $(D_C) $(D_S) $(D_BONUS_C) $(D_BONUS_S))

bonus:
				@printf "\n\033[1;35m 🏆 it's bonus time, baby 🏆\033[0m\n\n"
				@make SRC_C="$(SRC_BONUS_C)" SRC_S="$(SRC_BONUS_S)" HEADER="$(HEADER_BONUS)" all

clean:
				@$(RM) $(OBJ_C) $(OBJ_S) $(OBJ_BONUS_C) $(OBJ_BONUS_S) $(D_C) $(D_S) $(D_BONUS_C) $(D_BONUS_S)

fclean: 		clean
				@$(RM) $(NAME_C) $(NAME_S)
				@printf "\n\033[1;31m 🛑 client delete 🛑\033[0m\n\n"
				@printf "\033[1;31m 🛑 server delete 🛑\033[0m\n\n"

re: 			fclean all

.PHONY: 		all clean fclean re bonus