NAME		=	philo

SRCS		=	src/philo.c \
				src/init_data.c \
				src/utile.c \
				src/routine.c \
				src/init_philo.c \
				src/status.c \
				src/die.c \
				src/print.c

OBJS		=	$(SRCS:.c=.o)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
				rm -f $(OBJS)

fclean:		clean
				rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
