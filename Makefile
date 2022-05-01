NAME	= server

NAME2	= client

CFLAGS	= -Wall -Wextra -Werror

CC		= gcc

HEADER		= minitalk.h

SRCS	= server.c ft_utilities.c
SRCS2	= client.c ft_utilities.c

OBJS	= $(SRCS:.c=.o)
OBJS2	= $(SRCS2:.c=.o)

all: $(NAME2) $(NAME) 
%.o: 	%.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS) $(HEADER)
			$(CC) $(OBJS) -o ${NAME}

$(NAME2):	$(OBJS2) $(HEADER)
			$(CC) $(OBJS2) -o ${NAME2}

clean:
	-rm -rf $(OBJS) $(OBJS2)
	
fclean: clean
	-rm -rf $(NAME) $(NAME2)

re:		fclean all

.PHONY: all clean fclean re