#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	circle.setPosition(0,30);
	circle.setRadius(30);
	circle.setFillColor(sf::Color::Green);
	circle_Speed = 150.0f;
	circle_Right = true;
}
Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Escape)) {
		window->close();
	}
}

// Update game objects
void Level::update(float dt)
{
	//2,3
	window_Size = window->getSize();
	circle_Pos = circle.getPosition();
	float circle_DeltaX = dt * circle_Speed;

	if (circle_Pos.x > (window_Size.x - circle.getRadius() * 2)) {
	circle_Right = false;
	circle.setPosition(window_Size.x - circle_DeltaX, circle_Pos.y);
	}
	else if (circle_Pos.x + circle_DeltaX > window_Size.x - circle.getRadius()*2 && circle_Right == true) {
		circle_Right = false;
		circle_DeltaX = (circle_Pos.x + circle_DeltaX) - (window_Size.x - circle.getRadius()*2);
		circle.setPosition((window_Size.x - circle.getRadius() * 2) - circle_DeltaX, circle_Pos.y);
	}
	else if (circle_Pos.x - circle_DeltaX < 0  && circle_Right == false) {
		circle_Right = true;
		circle_DeltaX = 0 - (circle_Pos.x - circle_DeltaX);
		circle.setPosition(0 + circle_DeltaX, circle_Pos.y);
	}
	else if (circle_Right == true) {
		circle.setPosition(circle_Pos.x + circle_DeltaX, circle_Pos.y);
	}
	else {
		circle.setPosition(circle_Pos.x - circle_DeltaX, circle_Pos.y);
	}
	
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(circle);
	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 100, 100));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}