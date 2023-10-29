# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 09:17:22 by lhasmi            #+#    #+#              #
#    Updated: 2023/10/29 15:32:45 by lhasmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# install brew at 42
# rm -rf $HOME/goinfre/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew && echo 'export PATH=$HOME/goinfre/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update

PROGRAM := cub3D

SOURCES := src/parser/parser_tester.c src/parser/parse_map.c src/parser/parse_file.c src/parser/parse_utils.c src/parser/init.c
OBJECTS := $(SOURCES:.c=.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3 -fsanitize=address

MLX := MLX42/build/libmlx42.a
GLFW_PATH :=`brew --prefix glfw`
MLX_FLAGS := $(MLX) -L$(GLFW_PATH)  -framework Cocoa -framework OpenGL -framework IOKit -lglfw
LBFT_PATH := libft
LBFT := libft.a

.PHONY: all clean fclean re

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	cd MLX42 && cmake -B build && cmake --build build -j4
	cd libft && make
	echo "Building mlx and libft successfully completed."
	$(CC) $(CFLAGS) $(OBJECTS) $(LBFT_PATH)/$(LBFT) $(MLX_FLAGS) -o $(PROGRAM)
	echo "Built $(PROGRAM) successfully."

OBJDEPS = $(SOURCES:%.c=%.o)
$(OBJDEPS):
	$(CC) $(CFLAGS) -c $*.c -o $@

clean:
	rm -f $(OBJECTS)
	cd libft && make clean
	cd MLX42 && rm -rf build

fclean: clean
	rm -f $(PROGRAM)
	cd libft && make fclean
	cd MLX42 && rm -rf build

re: fclean all
