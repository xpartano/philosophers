# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/23 04:56:30 by jballest          #+#    #+#              #
#    Updated: 2021/05/05 21:42:23 by jballest         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two
CC = gcc

CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I .
LIBS = -lpthread

SRCS =	main.c						\
		philo_utils.c				\
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
	@printf "\e[1;32m"
	@printf "      ___           ___                       ___       ___               ___           ___           ___      \n"
	@printf "     /\  \         /\__\          ___        /\__\     /\  \             /\  \         /\__\         /\  \     \n"
	@printf "    /::\  \       /:/  /         /\  \      /:/  /    /::\  \            \:\  \       /:/ _/_       /::\  \    \n"
	@printf "   /:/\:\  \     /:/__/          \:\  \    /:/  /    /:/\:\  \            \:\  \     /:/ /\__\     /:/\:\  \   \n"
	@printf "  /::\~\:\  \   /::\  \ ___      /::\__\  /:/  /    /:/  \:\  \           /::\  \   /:/ /:/ _/_   /:/  \:\  \  \n"
	@printf " /:/\:\ \:\__\ /:/\:\  /\__\  __/:/\/__/ /:/__/    /:/__/ \:\__\         /:/\:\__\ /:/_/:/ /\__\ /:/__/ \:\__\ \n"
	@printf " \/__\:\/:/  / \/__\:\/:/  / /\/:/  /    \:\  \    \:\  \ /:/  /        /:/  \/__/ \:\/:/ /:/  / \:\  \ /:/  / \n"
	@printf "      \::/  /       \::/  /  \::/__/      \:\  \    \:\  /:/  /        /:/  /       \::/_/:/  /   \:\  /:/  /  \n"
	@printf "       \/__/        /:/  /    \:\__\       \:\  \    \:\/:/  /         \/__/         \:\/:/  /     \:\/:/  /   \n"
	@printf "                   /:/  /      \/__/        \:\__\    \::/  /                         \::/  /       \::/  /    \n"
	@printf "                   \/__/                     \/__/     \/__/                           \/__/         \/__/     \n"
	@printf "\e[0;37m"

.PHONY:			all clean fclean re
