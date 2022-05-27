# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 12:35:23 by nlouro            #+#    #+#              #
#    Updated: 2022/05/27 12:25:38 by nlouro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

C_FLAGS = -Wall -Wextra -Werror

C_FILES = philo.c ft_atoi.c forks.c log.c utils.c
O_FILES = $(C_FILES:%.c=%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(O_FILES)
	gcc $(C_FLAGS) $(O_FILES) -o $(NAME)

$(O_FILES):
	gcc -c $(C_FLAGS) $(C_FILES)

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
