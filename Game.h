#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	sf::Clock clock;

	sf::RectangleShape player1, player2;
	sf::RectangleShape ball;
	sf::RectangleShape middleLine;

	sf::Text text1, text2;
	sf::Font font;

	void initWindow();
	void initVars();
	void keyBoardInput();
	void ballMovement();

	float deltaTime;
	float player1Speed, player2Speed;

	float racketWidth, racketHeight;
	float racketOutlineThickness;

	int player1Score = 0, player2Score = 0;

	bool ballFuse = false;

	vector<float> player1Pos = { 0, 0 };
	vector<float> player2Pos = { 0, 0 };
	vector<float> ballPos = { 0, 0 };
	vector<float> ballSpeed = { 0, 0 };

public:
	Game();
	virtual ~Game();

	const bool isRunning() const;
	void updateEvents(float deltaTime);
	void update();
	void render();
};

