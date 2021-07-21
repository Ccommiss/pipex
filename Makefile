# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/20 14:50:16 by ccommiss          #+#    #+#              #
#    Updated: 2021/07/21 16:51:09 by ccommiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex


SRC_FOLD = ./srcs/

SRCS = $(SRC_FOLD)multipipe.c \
	$(SRC_FOLD)pipe_communicating.c \
	$(SRC_FOLD)utils.c \
	$(SRC_FOLD)utils/ft_strconcat.c \
	$(SRC_FOLD)utils/ft_split.c \
	$(SRC_FOLD)utils/ft_memdel.c \
	$(SRC_FOLD)utils/ft_strlen.c \
	$(SRC_FOLD)utils/ft_strdup.c \
	$(SRC_FOLD)utils/ft_putendl.c \
	$(SRC_FOLD)utils/ft_free_double_tab.c \
	$(SRC_FOLD)utils/ft_strncmp.c


LIB = $(SRC_FOLD)libft
INCLUDES = /includes/
FLAGS = -I.$(INCLUDES) -Wall -Werror -Wextra -fsanitize=address -fno-omit-frame-pointer
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

