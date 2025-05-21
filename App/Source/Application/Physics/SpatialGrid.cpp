#include "SpatialGrid.hpp"

void Physics::SpatialGrid::clearGrid()
{
	/*for (auto& cell : cells)
	{
		auto& balls = cell.second;
		balls.clear();
	}*/
	
	cells.clear();
}

void Physics::SpatialGrid::addBall(Ball* ball)
{
	BoundingBox aabb = ball->boundingBox;

	int startX = static_cast<int>(std::floor(aabb.min.x / cellSize));
	int endX = static_cast<int>(std::floor((aabb.max.x - 1e-5f) / cellSize));
	int startY = static_cast<int>(std::floor(aabb.min.y / cellSize));
	int endY = static_cast<int>(std::floor((aabb.max.y - 1e-5f) / cellSize));

	for (int x = startX; x <= endX; x++)
	{
		for (int y = startY; y <= endY; y++)
		{
			auto key = std::make_pair(x, y);
			cells[key].push_back(ball);
		}
	}
}

std::vector<std::pair<Physics::Ball*, Physics::Ball*>> Physics::SpatialGrid::getPotentialPairs()
{
	std::vector<std::pair<Ball*, Ball*>> pairs;
	std::unordered_set<std::pair<Ball*, Ball*>, PairHash> uniquePairs;

	for (const auto& [key, cellBalls] : cells)
	{
		int cellX = key.first;
		int cellY = key.second;

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				auto neighborKey = std::make_pair(cellX + i, cellY + j);
				auto neighbor = cells.find(neighborKey);
				if (neighbor == cells.end()) continue;

				for (Ball* a : cellBalls)
				{
					for (Ball* b : neighbor->second)
					{
						if (a == b) continue;

						if (neighborKey == key && b <= a) continue;

						if (a->boundingBox.overlaps(b->boundingBox))
						{
							auto orderedPair = (a < b) ? std::make_pair(a, b) : std::make_pair(b, a);
							if (uniquePairs.insert(orderedPair).second)
							{
								pairs.push_back(orderedPair);
							}
						}
					}
				}
			}
		}
	}

	return pairs;
}
