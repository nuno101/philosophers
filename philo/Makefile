# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 12:35:23 by nlouro            #+#    #+#              #
#    Updated: 2022/03/24 17:09:24 by nlouro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

#NAME, all, clean, fclean, re

C_FLAGS = -Wall -Wextra -Werror

C_FILES = philo.c
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
