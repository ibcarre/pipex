# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibaaziz <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/04 11:17:37 by ibaaziz           #+#    #+#              #
#    Updated: 2025/01/04 11:17:40 by ibaaziz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

INC = pipex.h\

INC_B = pipex_b.h\

SRC = ./pipex.c\
	./ft_split.c\
	./ft_strjoin.c\
	./pipex_utils.c

SRC_BONUS = ./bonus/pipex_b.c\
	./ft_split.c\
	./ft_strjoin.c\
	./pipex_utils.c

OBJ = $(SRC:.c=.o)

FLAGS += -Werror -Wextra -Wall -I $(INC) -g

$(NAME): $(OBJ)
	cc $(OBJ) -o $(NAME) $(FLAGS)

all: $(NAME)

%.o:%.c
	cc ${FLAGS} $< -c

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)


re: fclean all

