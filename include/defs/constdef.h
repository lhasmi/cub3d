#ifndef CONSTDEF_H
# define CONSTDEF_H

#define PI 3.14159265358979323846
#define PI_HALF PI / 2

typedef enum e_bearing
{
	BEARING_NORTH = 0,
	BEARING_EAST = 1,
	BEARING_SOUTH = 2,
	BEARING_WEST = 3,
}	t_bearing;

#endif