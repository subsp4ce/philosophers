# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: smiller <smiller@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/03/01 14:58:05 by smiller       #+#    #+#                  #
#    Updated: 2022/03/10 12:36:12 by smiller       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = philo
HEADER = includes/philo.h

SRC = 	src/main.c \
		src/ft.c \
		src/utils.c \
		src/parse_init.c \
		src/simulation.c \
		src/error_free.c

OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

obj/%.o: src/%.c $(HEADER)
	@mkdir -p obj/
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf obj/

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

.PHONY: all clean fclean re
