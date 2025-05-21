#pragma once

#include "../Vector2.hpp"

namespace Physics
{
	struct BoundingBox
	{
		Math::Vector2 min;
		Math::Vector2 max;

		bool overlaps(const BoundingBox& other) const
		{
			return (max.x > other.min.x && min.x < other.max.x) &&
				(max.y > other.min.y && min.y < other.max.y);
		}
	};

	struct Ball
	{
		Math::Vector2 acc;

		Math::Vector2 vel;

		Math::Vector2 force;

		Math::Vector2 pos;
		float radius;

		float mass = 1;
		float e = 1;

		BoundingBox boundingBox;

		Ball(Math::Vector2 pos, float r)
		{
			this->pos = pos;
			this->radius = r;
		}
	};
}