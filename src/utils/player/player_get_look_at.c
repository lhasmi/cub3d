#include <math.h>
#include "playerdef.h"
#include "vec.h"

t_vec	player_get_look_at(t_player *player, double offset)
{
	return (vec_create(
		cos(player->yaw + offset),
		sin(player->yaw + offset),
		0
	));
}
