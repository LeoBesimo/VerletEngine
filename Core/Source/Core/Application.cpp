#include "Application.hpp"
#include "Utils/Console.hpp"
#include <iostream>

Core::Application::Application()
{
	init();
}

Core::Application::~Application()
{
	destroy();
}

void Core::Application::start()
{
	init();

	running = true;

	using Clock = std::chrono::high_resolution_clock;
	auto lastTime = Clock::now();
	auto currentTime = Clock::now();
	float deltaTime = 1;

	while (running) 
	{
		currentTime = Clock::now();
		deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;

		for (std::shared_ptr<Window> window : m_Windows)
		{
			while (std::optional<sf::Event> event = window->pollEvent()) {
				ImGui::SFML::ProcessEvent(*window, event.value());

				if (event->is<sf::Event::Closed>()) {
					ImGui::SFML::Shutdown(*window);
					window->close();
					window->closed = true;
				}
				
				if (event->is<sf::Event::MouseMoved>()) {
					window->MousePosition = sf::Mouse::getPosition(*window);
				}
				handleWindowEvent(window, event);
			}
		}

		for (int i = m_Windows.size() - 1; i >= 0; i--) {
			if(m_Windows[i]->closed)
				m_Windows.erase(m_Windows.begin() + i);
		}

		for (std::shared_ptr<Window> window : m_Windows) 
		{
			ImGui::SFML::Update(*window, sf::seconds(deltaTime));
		}

		if(m_Windows.size() > 0)
			update(deltaTime);

		for (std::shared_ptr<Window> window : m_Windows) {
			ImGui::SFML::Render(*window);

			window->display();
		}

		if (m_Windows.size() == 0)
			running = false;

	}
}

std::shared_ptr<Core::Window> Core::Application::createWindow(unsigned int width, unsigned int height, std::string windowName)
{
	std::shared_ptr<Window> window = std::make_shared<Window>(width, height, windowName);
	m_Windows.push_back(window);
	if (!ImGui::SFML::Init(*window))
	{
		std::cout << Console::Foreground::RED << "ImGui Could not Be Initialized\n" << Console::Foreground::WHITE;
	}
	return window;
}

void Core::Application::init()
{
}

void Core::Application::handleWindowEvent(std::shared_ptr<Core::Window> window, std::optional<sf::Event> &event)
{

}

void Core::Application::update(float dt)
{
}

void Core::Application::destroy()
{
}
