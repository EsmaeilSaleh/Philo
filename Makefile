NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
IFLAGS		= -Iinclude

SRC_DIR		= src

SRCS		= main.c \
			  parsing/parsing.c \
			  init/init.c \
			  threads/routine.c \
			  monitor/monitor.c \
			  printing/print.c \
			  time/time_utils.c \
			  utils/ft_utils.c \
			  cleanup/cleanup.c

OBJS		= $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))
HEADER		= include/philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
