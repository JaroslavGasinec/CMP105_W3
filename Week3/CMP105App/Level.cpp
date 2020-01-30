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

	rect.setSize(sf::Vector2f(30, 30));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color::Red);
	rect_Direction = sf::Vector2f(0, 0);
	rect_Speed = 1000.0f;
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

	if (input->isKeyDown(sf::Keyboard::Up)) {
		rect_Direction.y -= 1;
		input->setKeyUp(sf::Keyboard::Up);
	}
	if (input->isKeyDown(sf::Keyboard::Down)) {
		rect_Direction.y += 1;
		input->setKeyUp(sf::Keyboard::Down);
	}
	if (input->isKeyDown(sf::Keyboard::Left)) {
		rect_Direction.x -= 1;
		input->setKeyUp(sf::Keyboard::Left);
	}
	if (input->isKeyDown(sf::Keyboard::Right)) {
		rect_Direction.x += 1;
		input->setKeyUp(sf::Keyboard::Right);
	}
	if (rect_Direction.x != 0) {
		rect_Direction.x = rect_Direction.x / abs(rect_Direction.x);
	}
	if (rect_Direction.y != 0) {
		rect_Direction.y = rect_Direction.y / abs(rect_Direction.y);
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
	
	//4
	rect_Pos = rect.getPosition();
	rect_Delta.x = dt * rect_Speed * rect_Direction.x;
	rect_Delta.y = dt * rect_Speed * rect_Direction.y;

	if (rect_Pos.x > window_Size.x - rect.getSize().x) {
		rect.setPosition(window_Size.x - rect.getSize().x, rect_Pos.y);
		rect_Pos = rect.getPosition();
	}
	if (!(rect_Pos.x + rect_Delta.x < 0) && !(rect_Pos.x + rect_Delta.x > window_Size.x - rect.getSize().x)){
		rect.setPosition(rect_Pos.x + rect_Delta.x, rect_Pos.y);
		rect_Pos.x += rect_Delta.x;
		rect_Direction.x = 0;
	}
	if (!(rect_Pos.y + rect_Delta.y < 0) && !(rect_Pos.y + rect_Delta.y > window_Size.y - rect.getSize().y)) {
		rect.setPosition(rect_Pos.x,rect_Pos.y + rect_Delta.y);
		rect_Direction.y = 0;
	}
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(circle);
	window->draw(rect);
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