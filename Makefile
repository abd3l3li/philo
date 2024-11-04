NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

BOLD      = \033[1m
CGREEN    = \033[32m
CCYAN     = \033[36m

SRC = philo.c utils.c thread.c thread_utils.c init.c

OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	@echo "$(BOLD)$(CGREEN)building the project...\033[0m"
	@${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean:
	@echo "$(BOLD)$(CGREEN)cleaning ...\033[0m"
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all fclean clean re
.SECONDARY: