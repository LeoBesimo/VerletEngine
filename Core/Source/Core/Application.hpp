#pragma once

#include <vector>
#include <memory>
#include <chrono>

#include "Graphics/Window.hpp"
#include "ImGui/imgui-SFML.h"

namespace Core
{
	class Application
	{
	public:
		Application();
		~Application();

		void start();

		std::shared_ptr<Window> createWindow(unsigned int width, unsigned int height, std::string windowName);

		virtual void init();
		virtual void handleWindowEvent(std::shared_ptr<Window> window, std::optional<sf::Event> &event);
		virtual void update(float dt);
		virtual void destroy();

	private:
		bool running = false;
		std::vector<std::shared_ptr<Window>> m_Windows;

	};
}