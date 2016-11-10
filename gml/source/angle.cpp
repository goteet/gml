#include "gmlangle.h"

namespace gml
{


	constexpr degree::degree(radian r) : value(r.value * r2d_factor)
	{
	}

	constexpr radian degree::to_radian() const
	{
		return radian(*this);
	}



}