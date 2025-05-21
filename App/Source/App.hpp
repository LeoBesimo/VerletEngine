#pragma once

#include <Core/Core.h>
#include <iostream>

class App :
	public Core::Application
{
public:

	App();

	void init() override;
	void handleWindowEvent(std::shared_ptr<Core::Window> window, std::optional<sf::Event> &event);
	void update(float dt) override;
	void destroy() override;


private:
	std::shared_ptr<Core::Window> windowPtr;
	std::shared_ptr<Core::Window> wind2;
};