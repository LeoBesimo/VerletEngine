#pragma once

namespace Physics
{
	struct BoundingBox
	{
		float xMin, xMax;
		float yMin, yMax;
	};

	struct Ball
	{
		float xAcc;
		float yAcc;

		float xVel;
		float yVel;

		float xForce = 0;
		float yForce = 0;

		float x;
		float y;
		float radius;

		float mass = 1;
		float e = 1;

		BoundingBox boundingBox;

		bool overlap(const Ball& other) const {
			return (boundingBox.xMax + x > other.boundingBox.xMin + other.x && boundingBox.xMin + x < other.boundingBox.xMax + other.x) &&
				(boundingBox.yMax +y > other.boundingBox.yMin + y && boundingBox.yMin + y < other.boundingBox.yMax + y);
		}

		Ball(float x, float y, float r)
		{
			this->x = x;
			this->y = y;
			this->radius = r;

			boundingBox.xMin = -radius;
			boundingBox.xMax = +radius;
			boundingBox.yMin = -radius;
			boundingBox.yMax = +radius;

			xVel = 0;
			yVel = 0;

			xAcc = 0;
			yAcc = 0;
		}
	};
}