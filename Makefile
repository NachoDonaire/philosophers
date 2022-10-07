SDIR = src/
NAME = philo
SRCS = philosophers.c ft_atoi.c
ODIR = objs/
CC = gcc
RM = rm -rf
CFLAGS = -Wextra -Werror -Wall
OBJS = $(addprefix $(SDIR), $(SRCS:.c=.o))
all:	$(NAME)
##obj:	
#	mkdir $(ODIR)
$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
clean:	
	$(RM) $(OBJS) $(ODIR)
fclean:	clean
	$(RM) $(NAME)
re:	fclean all

.PHONY: all fclean clean re



