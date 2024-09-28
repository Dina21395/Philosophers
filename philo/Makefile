NAME = philo
SRCS = main.c\
	pre_checker.c\
	philo_utilities.c\
	utilities.c\
	philo_init.c\
	philo_operations.c\
	utilities2.c\
	philo_operation2.c

CC = cc
CFLAGS =  -Wall -Wextra -Werror -g
OBJS = $(SRCS:.c=.o)
all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean:
	rm -f $(OBJS)
fclean:clean
	rm -f $(NAME)
re: fclean $(NAME)
.PHONY: all clean fclean re