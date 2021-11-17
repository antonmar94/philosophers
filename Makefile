
NAME = philosophers
LIBFT_NAME = libft.a
SRCS = ./src/philosophers.c \
		./src/philosophers_utils.c \
		./src/philosophers_functions.c \
		./src/philosophers_actions.c \

OBJS = ${SRCS:.c=.o}
LIBFT_DIR = ./libft/
CC = cc
CFLAGS = -Wall -Werror -Wextra 
RM = rm -f

%.o: %.c
	$(CC)  $(CFLAGS) -c $< -o $@
$(NAME): $(LIBFT_DIR)$(LIBFT_NAME) $(OBJS)
	$(CC) -o $(NAME)  $^
$(LIBFT_DIR)$(LIBFT_NAME): $(LIBFT_DIR)
	make bonus -C $(LIBFT_DIR)

all: $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re