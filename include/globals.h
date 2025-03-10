#include <vector>
#include <raylib.h>

#pragma once

namespace globals
{		// just for testing character collision
	inline std::vector<Rectangle> GetCollisionRectangles() 
	{ 
		return { { 90, 90, 50, 30 }, { 200, 200, 70, 10 }, { 400, 290, 30, 30 }, { 200, 110, 10, 70 } };
	}
}