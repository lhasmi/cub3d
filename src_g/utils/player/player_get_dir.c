#include "constdef.h"
#include "player.h"
#include "vec.h"

t_vec	player_get_left(t_player *player)
{
	return (player_get_look_at(player, -PI_HALF));
}

t_vec	player_get_right(t_player *player)
{
	return (player_get_look_at(player, PI_HALF));
}

t_vec	player_get_front(t_player *player)
{
	return (player_get_look_at(player, 0));
}

t_vec	player_get_back(t_player *player)
{
	return (player_get_look_at(player, PI));
}
