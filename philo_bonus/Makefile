# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 14:53:17 by pleander          #+#    #+#              #
#    Updated: 2024/09/23 11:42:03 by pleander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo_bonus
CC := cc
CFLAGS := -Wall -Wextra -Werror
CFILES := actions.c \
		  ft_atoi.c \
		  main.c \
		  make_sem_name.c \
		  philosopher.c \
		  print.c \
		  simulation.c \
		  simulation_utils.c \
		  table.c \
		  utils.c

OBJECTS := $(CFILES:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
