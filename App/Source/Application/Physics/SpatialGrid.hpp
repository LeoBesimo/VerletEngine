#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>

#include "Ball.hpp"

namespace Physics
{

    struct CellKeyHash
    {
        std::size_t operator()(const std::pair<int, int>& key) const
        {
            return std::hash<int>{}(key.first) ^ (std::hash<int>{}(key.second) << 1);
        }
    };

	class SpatialGrid
	{
    private:
        float cellSize;
        //std::unordered_map<std::pair<int, int>, std::vector<Ball*>, Physics::CellKeyHash> cells;
        std::map<std::pair<int, int>, std::vector<Ball*>> cells;
        // Convert a position to a grid cell key (for 2D)
        int getCellKey(float xPos, float yPos) const {
            int x = static_cast<int>(xPos / cellSize);
            int y = static_cast<int>(yPos / cellSize);
            return x * 1000 + y; // Arbitrary hash (adjust based on expected grid size)
        }

    public:
        SpatialGrid(float cellSize) : cellSize(cellSize) {}

        // Update an object's position in the grid
        void clearGrid();
        void addBall(Ball* ball);
        std::vector<std::pair<Ball*, Ball*>> getPotentialPairs();

        struct PairHash
        {
            std::size_t operator()(const std::pair<Ball*, Ball*>& p) const
            {
                std::size_t h1 = std::hash<Ball*>{}(p.first);
                std::size_t h2 = std::hash<Ball*>{}(p.second);
                return h1 ^ (h2 << 1);
            }
        };
    };
}