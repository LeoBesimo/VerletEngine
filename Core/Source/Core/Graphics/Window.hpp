#pragma once

#include <SFML/Graphics.hpp>

namespace Core
{
	class Window :
		public sf::RenderWindow
	{
		friend class Application;

	public:

		sf::Vector2i MousePosition;

		Window();
		Window(unsigned int width, unsigned int height);
		Window(unsigned int width, unsigned int height, std::string windowName);
		~Window();

		void rect(float x, float y, float width, float height);
		void line(float x1, float y1, float x2, float y2);
		void circle(float x, float y, float radius);

		void fill(int r = 0, int g = 0, int b = 0, int alpha = 255);
		void noFill();
		void stroke(int r = 0, int g = 0, int b = 0, int alpha = 255);
		void noStroke();

	private:
		bool closed = false;

		sf::Color m_StrokeColor;
		sf::Color m_FillColor;

		sf::CircleShape m_CircleShape;
		sf::RectangleShape m_RectangleShape;
		sf::Vertex m_Line[2];

	};
}