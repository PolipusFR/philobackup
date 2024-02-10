HEADER  := philo.h
NAME	:= philo
FLAGS	:= -Wall -Wextra -Werror -pthread
SRCS	:=	main.c \
			general_utils.c\
			philo_utils.c\
			init.c\
			supervisor.c\
			routine.c\
			exit_and_error.c\
                          
OBJS	:= $(SRCS:.c=.o)

%.o:%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) $(HEADER)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all 

.PHONY:		all clean fclean re