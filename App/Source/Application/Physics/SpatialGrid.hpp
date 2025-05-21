#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Ball.hpp"

namespace Physics
{
	class SpatialGrid
	{
    private:
        float cellSize; // Grid cell width/height (e.g., 64 units)
        std::unordered_map<int, std::vector<Ball*>> cells;
        // Convert a position to a grid cell key (for 2D)
        int getCellKey(float xPos, float yPos) const {
            int x = static_cast<int>(xPos / cellSize);
            int y = static_cast<int>(yPos / cellSize);
            return x * 1000 + y; // Arbitrary hash (adjust based on expected grid size)
        }

    public:
        SpatialGrid(float cellSize) : cellSize(cellSize) {}

        // Update an object's position in the grid
        void update(Ball* obj) {
            // Remove from old cells
            for (auto& cell : cells) {
                auto& objects = cell.second;
                objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
            }

            // Insert into new cells (cover all cells the AABB spans)
            BoundingBox aabb = obj->boundingBox;
            for (float x = aabb.xMin + obj->x; x < aabb.xMax + obj->x; x += cellSize) {
                for (float y = aabb.yMin + obj->y; y < aabb.yMax + obj->y; y += cellSize) {
                    int key = getCellKey(x,y);
                    cells[key].push_back(obj);
                }
            }
        }

        std::vector<std::pair<Ball*, Ball*>> getPotentialPairs() {
            std::vector<std::pair<Ball*, Ball*>> pairs;
            std::unordered_set<std::pair<Ball*, Ball*>, PairHash> uniquePairs;

            for (const auto& [key, cellBalls] : cells) {
                int cellX = key / 1000;
                int cellY = key % 1000;

                // Check neighboring cells (including diagonals)
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        int neighborKey = (cellX + dx) * 1000 + (cellY + dy);
                        auto neighborIt = cells.find(neighborKey);
                        if (neighborIt == cells.end()) continue;

                        // Check all pairs between current and neighbor cell
                        for (Ball* a : cellBalls) {
                            for (Ball* b : neighborIt->second) {
                                if (a == b) continue; // Skip self
                                auto orderedPair = (a < b) ? std::make_pair(a, b) : std::make_pair(b, a);
                                if (uniquePairs.insert(orderedPair).second) {
                                    if (a->overlap(*b)) {
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

    private:
        // Hash function for unique pair tracking
        struct PairHash {
            // Specialize for Ball* pairs
            std::size_t operator()(const std::pair<Ball*, Ball*>& p) const {
                std::hash<Ball*> hasher;
                return hasher(p.first) ^ hasher(p.second);
            }
        };
	};
}