# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 09:17:22 by lhasmi            #+#    #+#              #
#    Updated: 2023/11/16 20:57:50 by lhasmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# install brew at 42
# rm -rf $HOME/goinfre/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/goinfre/.brew && echo 'export PATH=$HOME/goinfre/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update

PROGRAM := cub3D

SOURCES := src/parser/parser_tester.c src/parser/parse_map.c src/parser/parse_file.c \
            src/parser/parse_utils.c src/parser/init.c src/parser/check_tile.c \
            src/parser/check_map.c
OBJECTS := $(SOURCES:src/%.c=Obj/%.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3 -fsanitize=address

MLX := MLX42/build/libmlx42.a
GLFW_PATH :=`brew --prefix glfw`
MLX_FLAGS := $(MLX) -L$(GLFW_PATH)  -framework Cocoa -framework OpenGL -framework IOKit -lglfw
LBFT_PATH := libft
LBFT := libft.a

.PHONY: all clean fclean re validtests

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	@mkdir -p Obj
	cd MLX42 && cmake -B build && cmake --build build -j4
	cd libft && make
	echo "Building mlx and libft successfully completed."
	$(CC) $(CFLAGS) $(OBJECTS) $(LBFT_PATH)/$(LBFT) $(MLX_FLAGS) -o $(PROGRAM)
	echo "Built $(PROGRAM) successfully."

Obj/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# 2>&1 syntax redirects stderr (file descriptor 2) to stdout
# (file descriptor 1), ensuring that both r captured in the log file.
validtests:
	@echo "Starting valid tests..." > validtests.log
	@echo "******************" >> validtests.log
	@files=$$(ls maps/valid/*.cub); \
	prev=""; \
	for file in $$files; do \
		if [ -n "$$prev" ]; then \
			echo "************************************" >> validtests.log; \
			echo "************************************" >> validtests.log; \
			echo "Running with $$prev" >> validtests.log; \
			./cub3D $$prev >> validtests.log 2>&1; \
			echo "Next file: $$file" >> validtests.log; \
		fi; \
		prev=$$file; \
	done; \
	if [ -n "$$prev" ]; then \
		echo "******************" >> validtests.log; \
		echo "Running with $$prev" >> validtests.log; \
		./cub3D $$prev >> validtests.log 2>&1; \
	fi
	@echo "******************" >> validtests.log
	@echo "All tests completed." >> validtests.log

clean:
	rm -rf Obj
	cd libft && make clean
	cd MLX42 && rm -rf build

fclean: clean
	rm -f $(PROGRAM)
	cd libft && make fclean
	cd MLX42 && rm -rf build

re: fclean all

PHONY: all clean fclean re validtests
