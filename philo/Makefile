
NAME = philo
SRCS = ./src/philo.c \
		./src/philo_utils.c \
		./src/philo_functions.c \
		./src/philo_actions.c \
		./src/philo_list_utils.c \
		./src/philo_time_utils.c

OBJS = ${SRCS:.c=.o}
CC = cc
CFLAGS = -Wall -Werror -Wextra 
RM = rm -f

all: $(NAME)

%.o: %.c
	$(CC)  $(CFLAGS) -c $< -o $@
$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $^ 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re