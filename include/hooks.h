#ifndef HOOKS_H
# define HOOKS_H

# include "MLX42/MLX42.h"

void	loop_hook(void *param);
void	resize_hook(int32_t width, int32_t height, void *param);
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param);
void	cursor_hook(double xpos, double ypos, void* param);

#endif