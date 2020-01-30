#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();
	sf::CircleShape circle;
	sf::Vector2u window_Size;
	sf::Vector2f circle_Pos;
	float circle_Speed;
	bool circle_Right;

	sf::RectangleShape rect;
	float rect_Speed;
	sf::Vector2f rect_Pos;
	sf::Vector2f rect_Delta;
	sf::Vector2f rect_Speed;

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
};