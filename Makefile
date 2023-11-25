# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbohm <gbohm@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 20:56:57 by lhasmi            #+#    #+#              #
#    Updated: 2023/11/25 21:29:02 by gbohm            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-I MLX42/include -I libft -I include -I include/defs
SAN_LDFLAG=
NAME=cub3D
SRC_L_DIR=src_l
SRC_G_DIR=src_g
OBJ_DIR=obj

SRC_L= $(SRC_L_DIR)/parser/parse_map.c $(SRC_L_DIR)/parser/parse_file.c \
		$(SRC_L_DIR)/parser/parse_utils.c $(SRC_L_DIR)/parser/init.c $(SRC_L_DIR)/parser/check_tile.c \
		$(SRC_L_DIR)/parser/check_map.c $(SRC_L_DIR)/parser/check_map_bis.c \
		$(SRC_L_DIR)/parser/parse_file_bis.c $(SRC_L_DIR)/parser/parse_utils2.c
SRC_G=$(SRC_G_DIR)/utils/dda/dda.c $(SRC_G_DIR)/utils/dda/dda_hit.c $(SRC_G_DIR)/utils/draw/draw_line.c $(SRC_G_DIR)/utils/draw/draw_pixel.c $(SRC_G_DIR)/utils/draw/draw_rect.c $(SRC_G_DIR)/utils/draw/draw_square.c $(SRC_G_DIR)/utils/hooks/controls.c $(SRC_G_DIR)/utils/hooks/hooks.c $(SRC_G_DIR)/utils/minimap/minimap_draw.c $(SRC_G_DIR)/utils/player/player_collide.c $(SRC_G_DIR)/utils/player/player_create.c $(SRC_G_DIR)/utils/player/player_get_dir.c $(SRC_G_DIR)/utils/player/player_get_look_at.c $(SRC_G_DIR)/utils/player/player_move.c $(SRC_G_DIR)/utils/ray.c $(SRC_G_DIR)/utils/scene/scene_draw.c $(SRC_G_DIR)/utils/scene/scene_free.c $(SRC_G_DIR)/utils/scene/scene_get.c $(SRC_G_DIR)/utils/scene/scene_is_wall.c $(SRC_G_DIR)/utils/setup/gnl_free.c $(SRC_G_DIR)/utils/setup/map_closed.c $(SRC_G_DIR)/utils/setup/parser.c $(SRC_G_DIR)/utils/setup/setup_pad_map.c $(SRC_G_DIR)/utils/tex/tex_blend.c $(SRC_G_DIR)/utils/tex/tex_get_pixel.c $(SRC_G_DIR)/utils/vec/vec_add_sub.c $(SRC_G_DIR)/utils/vec/vec_correct.c $(SRC_G_DIR)/utils/vec/vec_create.c $(SRC_G_DIR)/utils/vec/vec_dot_cross.c $(SRC_G_DIR)/utils/vec/vec_length.c $(SRC_G_DIR)/utils/vec/vec_normalize.c $(SRC_G_DIR)/utils/vec/vec_print.c $(SRC_G_DIR)/utils/vec/vec_scalar.c
OBJ=$(patsubst $(SRC_L_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_L)) $(patsubst $(SRC_G_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_G))

MLX=MLX42/build/libmlx42.a
LIBFT=libft/libft.a
GLFW_PATH=$(shell brew --prefix glfw)
DEPS=-lglfw -L $(GLFW_PATH) -framework Cocoa -framework OpenGL -framework IOKit

HEADERS=include/cub3d.h include/dda.h include/defs/constdef.h include/defs/playerdef.h include/defs/raydef.h include/defs/scenedef.h include/defs/vecdef.h include/draw.h include/hooks.h include/minimap.h include/player.h include/ray.h include/scene.h include/setup.h include/tex.h include/vec.h include/defs/constdef.h include/defs/playerdef.h include/defs/raydef.h include/defs/scenedef.h include/defs/vecdef.h

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

ifdef LEAKS
	SAN_LDFLAG += -L../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next -I ../LeakSanitize
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
	$(CC) $(CFLAGS) $(SAN_LDFLAG) -o $(NAME) $^ $(DEPS)
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
#	rm *.log

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
	@norminette $(SRC_L) $(SRC_G) $(HEADERS)

test: all
	./$(NAME) maps/bonus/gero.cub

.PHONY:
	all bonus clean fclean re norm test
