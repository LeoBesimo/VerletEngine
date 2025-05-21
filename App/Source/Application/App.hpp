#pragma once

#include <Core/Core.h>
#include <iostream>

#include "Physics/Integrator.hpp"
#include "Physics/SpatialGrid.hpp"

class App :
	public Core::Application
{
public:

	App();

	void init() override;
	void handleWindowEvent(std::shared_ptr<Core::Window> window, std::optional<sf::Event> &event);
	void update(float dt) override;
	void destroy() override;

	void addBall();


private:
	Physics::SpatialGrid grid = Physics::SpatialGrid(50.f);
	std::shared_ptr<Core::Window> windowPtr;

	std::vector<Physics::Ball> balls;

	Physics::Integrator integrator;

	using Clock = std::chrono::high_resolution_clock;
	std::chrono::steady_clock::time_point lastTime = Clock::now();
	std::chrono::steady_clock::time_point currentTime = Clock::now();
};