#include "Window.hpp"

Core::Window::Window() :
	sf::RenderWindow(sf::VideoMode({800,600}), "Window")
{
}

Core::Window::Window(unsigned int width, unsigned int height) :
	sf::RenderWindow(sf::VideoMode({ width, height }), "Window")
{
}

Core::Window::Window(unsigned int width, unsigned int height, std::string windowName) :
	sf::RenderWindow(sf::VideoMode({ width,height }), windowName)
{
}

Core::Window::~Window()
{
}

void Core::Window::rect(float x, float y, float width, float height)
{
	m_RectangleShape.setPosition(sf::Vector2f(x, y));
	m_RectangleShape.setSize(sf::Vector2f(width, height));
	m_RectangleShape.setFillColor(m_FillColor);
	m_RectangleShape.setOutlineColor(m_StrokeColor);
	m_RectangleShape.setOutlineThickness(1.f);

	draw(m_RectangleShape);
}

void Core::Window::line(float x1, float y1, float x2, float y2)
{
	m_Line[0] = sf::Vertex(sf::Vector2f(x1, y1), m_StrokeColor);
	m_Line[1] = sf::Vertex(sf::Vector2f(x2, y2), m_StrokeColor);

	draw(m_Line, 2, sf::PrimitiveType::Lines);
}

void Core::Window::circle(float x, float y, float radius)
{
	m_CircleShape.setPosition(sf::Vector2f(x - radius, y - radius));
	m_CircleShape.setRadius(radius);
	m_CircleShape.setFillColor(m_FillColor);
	m_CircleShape.setOutlineColor(sf::Color::Red);	
	m_CircleShape.setOutlineThickness(1.f);

	draw(m_CircleShape);
}

void Core::Window::fill(int r, int g, int b, int alpha)
{
	m_FillColor = sf::Color(r, g, b, alpha);
}

void Core::Window::noFill()
{
	m_FillColor = sf::Color::Transparent;
}

void Core::Window::stroke(int r, int g, int b, int alpha)
{	
	m_StrokeColor = sf::Color(r, g, b, alpha);
}

void Core::Window::noStroke()
{
	m_StrokeColor = sf::Color::Transparent;
}