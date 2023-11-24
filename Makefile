# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 20:56:57 by lhasmi            #+#    #+#              #
#    Updated: 2023/11/25 00:45:42 by lhasmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC=cc
CFLAGS=-I MLX42/include -I libft -I include -I include/defs
NAME=cub3D
SRC_L_DIR=src_l
SRC_G_DIR=src_g
OBJ_DIR=obj

SRC_L= $(SRC_L_DIR)/parser/parse_map.c $(SRC_L_DIR)/parser/parse_file.c \
		$(SRC_L_DIR)/parser/parse_utils.c $(SRC_L_DIR)/parser/init.c $(SRC_L_DIR)/parser/check_tile.c \
		$(SRC_L_DIR)/parser/check_map.c $(SRC_L_DIR)/parser/check_map_bis.c \
		$(SRC_L_DIR)/parser/check_file_bis.c $(SRC_L_DIR)/parser/parse_utils2.c
SRC_G=$(filter-out $(SRC_G_DIR)/main.c, $(shell find $(SRC_G_DIR) -type f -name '*.c'))
OBJ=$(patsubst $(SRC_L_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_L)) $(patsubst $(SRC_G_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_G))

MLX=MLX42/build/libmlx42.a
LIBFT=libft/libft.a
GLFW_PATH=$(shell brew --prefix glfw)
DEPS=-lglfw -L $(GLFW_PATH) -framework Cocoa -framework OpenGL -framework IOKit

HEADERS=$(wildcard include/*.h) $(wildcard include/defs/*.h)

ifndef LENIENT
	CFLAGS += -Wall -Werror -Wextra
endif

ifdef DEBUG
	CFLAGS += -g -fsanitize=address
endif

ifndef LAILA
	SRC_G += $(SRC_G_DIR)/main.c
else
	SRC_L += $(SRC_L_DIR)/parser/parser_tester.c
endif

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_L_DIR)/%.c $(HEADERS) Makefile
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_G_DIR)/%.c $(HEADERS) Makefile
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

$(LIBFT):
	cd libft && make
	@echo "*********************************************  ***************************************"
	@echo "*********************************************    Building libft successfully completed."
	@echo "*********************************************  ***************************************"

$(MLX):
	cd MLX42 && cmake -B build && cmake --build build -j4
	@echo "*********************************************  ***************************************"
	@echo "*********************************************    Building mlx successfully completed."
	@echo "*********************************************  ***************************************"
# git clone https://github.com/codam-coding-college/MLX42.git

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(DEPS)
	@echo "Built $(NAME) successfully."

valid:
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

invalid:
	@echo "Starting invalid tests..." > invalidtests.log
	@echo "Current directory: $$(pwd)" >> invalidtests.log
	@echo "******************" >> invalidtests.log
	@files=$$(ls maps/invalid/*.cub); \
	prev=""; \
	for file in $$files; do \
		if [ -n "$$prev" ]; then \
			echo "************************************" >> invalidtests.log; \
			echo "************************************" >> invalidtests.log; \
			echo "Running with $$prev" >> invalidtests.log; \
			./cub3D $$prev >> invalidtests.log 2>&1 || true; \
			echo "Next file: $$file" >> invalidtests.log; \
		fi; \
		prev=$$file; \
	done; \
	if [ -n "$$prev" ]; then \
		echo "******************" >> invalidtests.log; \
		echo "Running with $$prev" >> invalidtests.log; \
		./cub3D $$prev >> invalidtests.log 2>&1 || true; \
	fi
	@echo "******************" >> invalidtests.log
	@echo "All tests completed." >> invalidtests.log

bonusmaps:
	@echo "Starting bonus tests..." > bonusmaps.log
	@echo "Current directory: $$(pwd)" >> bonusmaps.log
	@echo "******************" >> bonusmaps.log
	@files=$$(ls maps/bonus/*.cub); \
	prev=""; \
	for file in $$files; do \
		if [ -n "$$prev" ]; then \
			echo "************************************" >> bonusmaps.log; \
			echo "************************************" >> bonusmaps.log; \
			echo "Running with $$prev" >> bonusmaps.log; \
			./cub3D $$prev >> bonusmaps.log 2>&1 || true; \
			echo "Next file: $$file" >> bonusmaps.log; \
		fi; \
		prev=$$file; \
	done; \
	if [ -n "$$prev" ]; then \
		echo "******************" >> bonusmaps.log; \
		echo "Running with $$prev" >> bonusmaps.log; \
		./cub3D $$prev >> bonusmaps.log 2>&1 || true; \
	fi
	@echo "******************" >> bonusmaps.log
	@echo "All tests completed." >> bonusmaps.log

clean:
	rm -rf $(OBJ_DIR)
	@echo "Cleaned $(NAME) successfully."
	cd libft && make clean
	@echo "Cleaned libft successfully."
	cd MLX42 && rm -rf build
	@echo "Cleaned mlx successfully."
	rm *.log

fclean: clean
	rm -f $(NAME)
	@echo "Cleaned $(NAME) successfully."
	cd libft && make fclean
	@echo "Cleaned libft successfully."
	cd MLX42 && rm -rf build
	@echo "Cleaned mlx successfully."

reset: fclean
	rm -rf $(MLX)

re: fclean all

norm:
	norminette $(SRC) $(HEADERS)

test: all
	./$(NAME) maps/bonus/gero.cub

.PHONY:
	all bonus clean fclean re norm
