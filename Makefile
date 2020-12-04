# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 13:58:56 by fsugimot          #+#    #+#              #
#    Updated: 2020/12/04 14:30:58 by fsugimot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_mini_ls
DEBUG_NAME := ft_mini_ls_d
SRCS := main.c
OBJS := $(subst .c,.o,$(SRCS))
CC := gcc
CFLAGS := -Wall -Werror -Wextra

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $<
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME) 
re: fclean $(NAME)
debug: 
	$(CC) -ggdb  $(SRCS) -o $(DEBUG_NAME) $<
.PHONY: clean fclean re