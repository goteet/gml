#include "../include/gmlrotation.h"

namespace gml
{
	euler::euler() : roll(0), pitch(0), yaw(0) { }

	euler::euler(float roll, float pitch, float yaw) : roll(roll), pitch(pitch), yaw(yaw) { }

	euler::euler(const vec3& v) : roll(v.x), pitch(v.y), yaw(v.z) { }
}