
NAME = philo
NAME_BONUS = philo_bonus
SRCS = ./src/philo.c \
		./src/philo_utils.c \
		./src/philo_functions.c \
		./src/philo_actions.c \
		./src/philo_list_utils.c \
		./src/philo_time_utils.c

SRCS_BONUS = ../philo_bonus/src/philo_bonus.c \
			../philo_bonus/src/philo_utils_bonus.c \
			../philo_bonus/src/philo_functions_bonus.c \
			../philo_bonus/src/philo_actions_bonus.c \
			../philo_bonus/src/philo_list_utils_bonus.c \
			../philo_bonus/src/philo_time_utils_bonus.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS.c=.o} 

CC = cc
CFLAGS = -Wall -Werror -Wextra 
RM = rm -f

all: $(NAME)

bonus: $(SRCS_BONUS)
	$(CC)  $(CFLAGS) -c $< -o $@
$(NAME_BONUS) : $(OBJ_BONUS)
	$(CC) -o $(NAME_BONUS) $^

%.o: %.c
	$(CC)  $(CFLAGS) -c $< -o $@
$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $^ 

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: clean all

.PHONY: all clean fclean re