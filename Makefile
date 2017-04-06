# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amehmeto <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/12 02:44:46 by amehmeto          #+#    #+#              #
#    Updated: 2017/04/07 00:35:18 by amehmeto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re 

NAME = fillit
FILE = main.c \
	   fillit_is_sample_valid.c \
	   fillit_displayer_no_color.c \
	   fillit_resolver.c \
	   fillit_encoder.c \
	   fillit_square_vs_tetri.c
OBJ = $(FILE:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Weverything 

all: $(NAME)

$(NAME): $(OBJ)
	make -C Libft 
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) Libft/libft.a

%.o: src/%.c
	$(CC) -c $< $(FLAGS)

clean:
	make -C Libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C Libft fclean
	rm -rf $(NAME)

re: fclean all
