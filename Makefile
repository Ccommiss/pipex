# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/20 14:50:16 by ccommiss          #+#    #+#              #
#    Updated: 2021/07/20 20:58:04 by ccommiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex


SRC_FOLD = ./srcs/

SRCS = $(SRC_FOLD)multipipe.c \
	$(SRC_FOLD)pipe_communicating.c \
	$(SRC_FOLD)utils.c \


LIB = $(SRC_FOLD)libft
INCLUDES = /includes/
FLAGS = -I.$(INCLUDES) -I$(LIB) -Wall -Werror -Wextra -fsanitize=address -fno-omit-frame-pointer
OBJS = $(SRCS:.c=.o)
CC = clang -g $(FLAGS)


all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIB)
	$(CC) $(OBJS) -L$(LIB) -lft -o $(NAME)

clean :
	make clean -C $(LIB)
	rm $(OBJS)

fclean : clean
	make fclean -C $(LIB)
	rm $(NAME)

re : fclean all

