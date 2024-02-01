HEADER  := philo.h
NAME	:= philo
CC		:= gcc
FLAGS	:= -Wall -Wextra -Werror -g3
SRCS	:=	main.c \
			general_utils.c\
			philo_utils.c\
			init.c\
			ft_atoi.c \
                          
OBJS	:= $(SRCS:.c=.o)

%.o:%.c $(HEADER)clea
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

RM		    := rm -f

$(NAME):	$(OBJS) $(HEADER)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all 

.PHONY:		all clean fclean re