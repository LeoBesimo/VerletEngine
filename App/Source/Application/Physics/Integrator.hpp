#pragma once

#include <math.h>
#include "Ball.hpp"

namespace Physics
{
	class Integrator
	{
	public:
		Integrator();

		void verletIntegration(Ball& ball, float dt);
		void eulerIntegration(Ball& ball, float dt);
		void rebound(Ball& ball);

		bool detectCollision(Ball& a, Ball& b);
		void resolveCollision(Ball& a, Ball& b);
		void solveOverlap(Ball& a, Ball& b);
	};
}