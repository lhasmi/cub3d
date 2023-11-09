CC=cc
CFLAGS=-I MLX42/include -I include -I include/defs
NAME=cub3D
SRC_DIR=src
OBJ_DIR=obj

SRC=$(shell find src -type f -name '*.c')
OBJ=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

MLX=MLX42/build/libmlx42.a
GLFW_PATH := $(shell brew --prefix glfw)
DEPS=-lglfw -L $(GLFW_PATH) -framework Cocoa -framework OpenGL -framework IOKit

HEADERS=$(wildcard include/*.h) $(wildcard include/defs/*.h)

ifndef LENIENT
	CFLAGS += -Wall -Werror -Wextra
endif

ifdef DEBUG
	CFLAGS += -g
endif

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

$(MLX):
	git clone https://github.com/codam-coding-college/MLX42.git
	(cd MLX42 && cmake -B build && cmake --build build)

$(NAME): $(MLX) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(DEPS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

reset: fclean
	rm -rf MLX42

re: fclean all

norm:
	norminette $(SRC) $(HEADERS)

test: all
	./$(NAME)

aaa:
	@echo $(SRC)

.PHONY:
	all bonus clean fclean re norm
