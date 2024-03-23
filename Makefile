########################VARS##################################
NAME	= philo

SRCS	= th_h.c ft_init.c ft_life_cycle.c utils.c ft_libft.c utils_2.c

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

OBJS	= $(SRCS:.c=.o)


#######################RULES##################################
all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:	clean fclean re
#################################################################
