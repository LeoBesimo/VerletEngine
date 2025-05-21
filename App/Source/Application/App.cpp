#include "App.hpp"


App::App() :
	Core::Application()
{
}

void App::init()
{
	std::cout << "Creating Window\n";

	windowPtr = createWindow(1400, 1200, "App Window");
	windowPtr->fill(0, 255, 0);
	windowPtr->stroke(255, 255, 255);
	windowPtr->setFramerateLimit(60);


}

void App::handleWindowEvent(std::shared_ptr<Core::Window> window, std::optional<sf::Event> &event)
{
	if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		std::cout << (int)keyPressed->code << "\n";
	if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
		addBall();
}

void App::update(float dt)
{
	//ImGui::SFML::SetCurrentWindow(*windowPtr);
	//ImGui::ShowDemoWindow();

	ImGui::Begin("FPS Display");

	std::stringstream stream;
	stream << "FPS " << 1 / dt << "\n" << "Ball Count:" << balls.size() << "\n";

	ImGui::Text(stream.str().c_str());

	ImGui::End();

	

	for (Physics::Ball& ball : balls) {
		integrator.verletIntegration(ball, dt);
		integrator.rebound(ball);

		/*for (Physics::Ball& ball2 : balls) {
			if (&ball == &ball2)
				continue;
			if (integrator.detectCollision(ball, ball2))
				integrator.resolveCollision(ball, ball2);
		}*/
	}

	for (auto& obj : balls) {
		grid.update(&obj);
	}

	auto potentialPairs = grid.getPotentialPairs();

	// Check narrow phase with SAT
	for (const auto& pair : potentialPairs) {
		if (integrator.detectCollision(*pair.first, *pair.second)) {
			integrator.resolveCollision(*pair.first, *pair.second);
		}
	}

	windowPtr->clear();

	for (Physics::Ball& ball : balls) {
		windowPtr->circle(ball.x, ball.y, ball.radius);
	}
}

void App::destroy()
{
}

void App::addBall()
{
	for(int i =0; i< 30; i++){
		Physics::Ball ball = Physics::Ball(windowPtr->MousePosition.x, windowPtr->MousePosition.y, 25);
		ball.xVel = rand() % (60 + 60 + 1) - 120;
		ball.yVel = rand() % (60 + 60 + 1) - 120;

		balls.push_back(ball);
	}
}
