#include "App.hpp"


App::App() :
	Core::Application()
{
}

void App::init()
{
	std::cout << "Creating Window\n";

	windowPtr = createWindow(800, 600, "App Window");
	//windowPtr->fill(0, 255, 0);
	windowPtr->noFill();
	windowPtr->stroke(255, 0, 255);
	windowPtr->setFramerateLimit(60);

}

void App::handleWindowEvent(std::shared_ptr<Core::Window> window, std::optional<sf::Event> &event)
{
	if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		std::cout << (int)keyPressed->code << "\n";
}

void App::update(float dt)
{
	ImGui::SFML::SetCurrentWindow(*windowPtr);
	ImGui::ShowDemoWindow();

	windowPtr->clear();
	windowPtr->circle(windowPtr->MousePosition.x, windowPtr->MousePosition.y, 100);
}

void App::destroy()
{
}