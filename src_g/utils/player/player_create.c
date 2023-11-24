#include "playerdef.h"

t_player	player_create(t_vec position, double yaw)
{
	return ((t_player){position, yaw});
}
