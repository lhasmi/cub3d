# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 20:56:57 by lhasmi            #+#    #+#              #
#    Updated: 2023/11/22 22:35:05 by lhasmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC=cc
CFLAGS=-I MLX42/include -I include -I include/defs
NAME=cub3D
SRC_L_DIR=src_l
SRC_G_DIR=src_g
OBJ_DIR=obj

SRC_L= $(SRC_L_DIR)/parser/parse_map.c $(SRC_L_DIR)/parser/parse_file.c \
		$(SRC_L_DIR)/parser/parse_utils.c $(SRC_L_DIR)/parser/init.c $(SRC_L_DIR)/parser/check_tile.c \
		$(SRC_L_DIR)/parser/check_map.c
SRC_G=$(filter-out $(SRC_G_DIR)/main.c, $(shell find $(SRC_G_DIR) -type f -name '*.c'))
OBJ=$(patsubst $(SRC_L_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_L)) $(patsubst $(SRC_G_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_G))

MLX=MLX42/build/libmlx42.a
LIBFT=libft/libft.a
GLFW_PATH=$(shell brew --prefix glfw)
DEPS=-lglfw -L $(GLFW_PATH) -framework Cocoa -framework OpenGL -framework IOKit

HEADERS=$(wildcard include/*.h) $(wildcard include/defs/*.h)

ifndef LENIENT
	CFLAGS += -Wall -Werror -Wextra -fsanitize=address
endif

ifdef DEBUG
	CFLAGS += -g
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
	(cd libft && make)

$(MLX):
	cd MLX42 && cmake -B build && cmake --build build
# git clone https://github.com/codam-coding-college/MLX42.git

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(DEPS)

clean:
	rm -rf $(OBJ_DIR)
	(cd libft && make clean)

fclean: clean
	rm -f $(NAME)
	(cd libft && make fclean)

reset: fclean
	rm -rf MLX42

re: fclean all

norm:
	norminette $(SRC) $(HEADERS)

test: all
	./$(NAME) maps/gero.cub

.PHONY:
	all bonus clean fclean re norm
