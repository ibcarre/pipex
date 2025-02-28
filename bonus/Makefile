# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibaaziz <ibaaziz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/04 11:17:37 by ibaaziz           #+#    #+#              #
#    Updated: 2025/02/24 17:13:38 by ibaaziz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipexb

INC = pipex_b.h\

SRC = ./pipex_b.c\
	./pipex_b2.c\
	./ft_split.c\
	./ft_strjoin.c\
	./pipex_utils.c\
	./get_next_line.c\
	./get_next_line_utils.c\

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

