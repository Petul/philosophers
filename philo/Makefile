# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 14:53:17 by pleander          #+#    #+#              #
#    Updated: 2024/09/23 11:42:11 by pleander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := cc
CFLAGS := -Wall -Wextra -Werror
CFILES := forks.c \
		  ft_atoi.c \
		  last_meal.c \
		  main.c \
		  n_meals.c \
		  philosopher.c \
		  print.c \
		  state.c \
		  simulation.c \
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
