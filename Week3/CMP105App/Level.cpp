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

	rect2.setSize(sf::Vector2f(30, 30));
	rect2.setPosition(21, 35);
	rect2.setFillColor(sf::Color::Magenta);
	rect2_Direction = sf::Vector2f(1, -1);
	rect2_Speed = 150.0f;
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
	float circle_DeltaX = dt * circle_Speed * circle_Right;

	if (circle_Pos.x > (window_Size.x - circle.getRadius() * 2)) {
	circle_Right = -1.0f;
	circle.setPosition(window_Size.x - circle_DeltaX, circle_Pos.y);
	}
	else if (circle_Pos.x + circle_DeltaX > window_Size.x - circle.getRadius()*2) {
		circle_Right = -1.0f;
		circle_DeltaX = (window_Size.x - circle.getRadius() * 2) - (circle_Pos.x + circle_DeltaX);
	}
	else if (circle_Pos.x + circle_DeltaX < 0) {
		circle_Right = 1.0f;
		circle_DeltaX = 0 - (circle_Pos.x - circle_DeltaX);
	}
	circle.setPosition(circle_Pos.x + circle_DeltaX, circle_Pos.y);

	//4
	rect_Pos = rect.getPosition();
	rect_Delta.x = dt * rect_Speed * rect_Direction.x;
	rect_Delta.y = dt * rect_Speed * rect_Direction.y;

	if (rect_Pos.x > window_Size.x - rect.getSize().x) {
		rect.setPosition(window_Size.x - rect.getSize().x, rect_Pos.y);
		rect_Pos = rect.getPosition();
	}
	if (rect_Pos.x + rect_Delta.x < 0 || rect_Pos.x + rect_Delta.x > window_Size.x - rect.getSize().x){
		rect_Delta.x = 0;
	}
	if (rect_Pos.y + rect_Delta.y < 0 || rect_Pos.y + rect_Delta.y > window_Size.y - rect.getSize().y) {
		rect_Delta.y = 0;
	}
	rect.setPosition(rect_Pos.x + rect_Delta.x, rect_Pos.y + rect_Delta.y);
	rect_Direction = sf::Vector2f(0,0);

	//5
	rect2_Pos = rect2.getPosition();
	rect2_Delta.x = dt * rect2_Speed * rect2_Direction.x;
	rect2_Delta.y = dt * rect2_Speed * rect2_Direction.y;

	if (rect2_Pos.x > window_Size.x - rect2.getSize().x) {
		rect2.setPosition(window_Size.x - rect2.getSize().x, rect2_Pos.y);
		rect2_Pos = rect2.getPosition();
	}

	if (rect2_Pos.x + rect2_Delta.x > window_Size.x - rect2.getSize().x) {
		rect2_Delta.x = (window_Size.x - rect2.getSize().x) - (rect2_Pos.x + rect2_Delta.x);
		rect2_Direction.x *= (-1);
	}
	if (rect2_Pos.y + rect2_Delta.y > window_Size.y - rect2.getSize().y) {
		rect2_Delta.y = (window_Size.y - rect2.getSize().y) - (rect2_Pos.y + rect2_Delta.y);
		rect2_Direction.y *= (-1);
	}
	if (rect2_Pos.x + rect2_Delta.x < 0) {
		rect2_Delta.x = 0 - (rect2_Pos.x + rect2_Delta.x);
		rect2_Direction.x *= (-1);
	}
	if (rect2_Pos.y + rect2_Delta.y < 0) {
		rect2_Delta.y = 0 - (rect2_Pos.y + rect2_Delta.y);
		rect2_Direction.y *= (-1);
	}
	rect2.setPosition(rect2_Pos.x + rect2_Delta.x, rect2_Pos.y + rect2_Delta.y);
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(circle);
	window->draw(rect);
	window->draw(rect2);
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