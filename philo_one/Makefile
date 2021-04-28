# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/23 04:56:30 by jballest          #+#    #+#              #
#    Updated: 2021/04/28 15:10:05 by jballest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
CC = gcc

CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I .
LIBS = -lpthread

SRCS =	main.c						\
		init.c						\
		utils.c						\
		errors.c					\
		threads.c					\
		philosophers.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): printinfo $(OBJS)
				gcc ${CFLAGS} $(INCLUDES) ${OBJS}  ${LIBS}  -o ${NAME}

clean:
				-@rm -rf $(OBJS) $(BONUS_OBJS)

fclean:			clean
				-@rm -rf $(NAME)

re:				fclean $(NAME)

printinfo:
	clear
	@echo "\033[1;32m"
	@echo "        _     _ _                        "
	@echo "       | |   (_) |                       "
	@echo "  _ __ | |__  _| | ___   ___  _ __   ___ "
	@echo " | '_ \\| '_ \\| | |/ _ \\ / _ \\| '_ \\ / _ \\"
	@echo " | |_) | | | | | | (_) | (_) | | | |  __/"
	@echo " | .__/|_| |_|_|_|\\___/ \\___/|_| |_|\\___|"
	@echo " | |                ______               "
	@echo " |_|               |______|              "
	@echo "\033[0m"

.PHONY:			all clean fclean re
