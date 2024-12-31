#include "Game.h"
#include "Game.h"

void Game::initWindow()
{
	this->videoMode.height = 900;
	this->videoMode.width = 1400;

	this->window = new sf::RenderWindow(this->videoMode, "Interactive Grid");
	this->window->setFramerateLimit(60);

	player1Speed = 700;
	player2Speed = 700;
	ballSpeed[0] = 600;
	ballSpeed[1] = 600;
	player1Pos[0] = 100; player1Pos[1] = videoMode.height / 2;

	this->player1.setOutlineThickness(10);
	this->player1.setOutlineColor(sf::Color(255, 255, 255));
	this->player1.setSize(sf::Vector2f(70.f, 300.f));
	this->player1.setFillColor(sf::Color(0, 0, 0));
	this->player1.setPosition(sf::Vector2f(player1Pos[0], player1Pos[1]));
	
	racketWidth = player1.getSize().x + player1.getOutlineThickness();
	racketHeight = player1.getSize().y ;

	racketOutlineThickness = player1.getOutlineThickness();
	

	this->player2.setOutlineThickness(10);
	this->player2.setOutlineColor(sf::Color(255, 255, 255));
	this->player2.setSize(sf::Vector2f(70.f, 300.f));
	this->player2.setFillColor(sf::Color(0, 0, 0));
	player2Pos[0] = videoMode.width - 100 - player2.getSize().x; player2Pos[1] = videoMode.height / 2;
	this->player2.setPosition(sf::Vector2f(player2Pos[0], player2Pos[1]));

	ballPos[0] = videoMode.width / 2; ballPos[1] = videoMode.height / 2;

	this->ball.setOutlineThickness(10);
	this->ball.setOutlineColor(sf::Color(255, 0, 60));
	this->ball.setSize(sf::Vector2f(30.f, 30.f));
	this->ball.setFillColor(sf::Color(255, 0, 60));
	this->ball.setPosition(sf::Vector2f(ballPos[0], ballPos[1]));

	this->middleLine.setSize(sf::Vector2f(20.f, videoMode.height));
	this->middleLine.setFillColor(sf::Color::White);
	this->middleLine.setPosition(sf::Vector2f(videoMode.width / 2, 9));

	if (!font.loadFromFile("Minecraft.ttf"))
		std::cout << "TEXTURE ERROR \n";

	text1.setFont(font);
	text1.setString("Score: " + std::to_string(player1Score));
	text1.setCharacterSize(50);
	text1.setPosition(0 + 150, 0);
	text1.setFillColor(sf::Color::White);
	text1.setStyle(sf::Text::Bold);

	text2.setFont(font);
	text2.setString("Score: " + std::to_string(player2Score));
	text2.setCharacterSize(50);
	text2.setPosition(videoMode.width / 2 + 150, 0);
	text2.setFillColor(sf::Color::White);
	text2.setStyle(sf::Text::Bold);
}

void Game::initVars()
{
	this->window = nullptr;
}

Game::Game()
{
	this->initVars();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::isRunning() const
{
	return this->window && this->window->isOpen();
}

void Game::keyBoardInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player1Pos[1]  - racketOutlineThickness >= 0.f) // Move up
		player1Pos[1] -= player1Speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player1Pos[1] + racketHeight + racketOutlineThickness <= this->videoMode.height) // Move down
		player1Pos[1] += player1Speed * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player2Pos[1] - racketOutlineThickness >= 0.f) // Move up
		player2Pos[1] -= player2Speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player2Pos[1] + racketHeight + racketOutlineThickness <= this->videoMode.height) // Move down
		player2Pos[1] += player2Speed * deltaTime;
}

void Game::ballMovement()
{

	if (ballPos[1] < 0 || ballPos[1] > this->videoMode.height)
		ballSpeed[1] = -ballSpeed[1];
	if (ballPos[0] < 0) {		
		ballSpeed[0] = -ballSpeed[0];
		player2Score++;
		ballPos[0] = videoMode.width / 2; ballPos[1] = videoMode.height / 2;
		text2.setString("Score: " + std::to_string(player2Score));
	}		
	if (ballPos[0] > this->videoMode.width) {		
		ballSpeed[0] = -ballSpeed[0];	
		player1Score++;
		ballPos[0] = videoMode.width / 2; ballPos[1] = videoMode.height / 2;
		text1.setString("Score: " + std::to_string(player1Score));
	}
	if (ballPos[0] < player2Pos[0]
		&& ballPos[0] > player1Pos[0]
		|| ballPos[0] == videoMode.width / 2) 
		ballFuse = false;
		
	if (ballPos[0] >= player1Pos[0] // left to right
		&& ballPos[0] <= player1Pos[0] + racketWidth + 10 // right to left
		&& ballPos[1] + ball.getSize().y + racketOutlineThickness > player1Pos[1]  // right to left
		&& ballPos[1] - racketOutlineThickness < player1Pos[1] + racketHeight
		&& !ballFuse) 
	{
		ballSpeed[0] = -ballSpeed[0];
		ballFuse = true;}
	
	if (ballPos[0] + ball.getSize().x + racketOutlineThickness >= player2Pos[0]
		&& ballPos[0] <= player2Pos[0]
		&& ballPos[1] + ball.getSize().y + racketOutlineThickness > player2Pos[1]
		&& ballPos[1] - racketOutlineThickness < player2Pos[1] + racketHeight
		&& !ballFuse) 
	{
		ballFuse = true;
		ballSpeed[0] = -ballSpeed[0];}
	
	ballPos[0] -= ballSpeed[0] * deltaTime;
	ballPos[1] += ballSpeed[1] * deltaTime;
	this->ball.setPosition(ballPos[0], ballPos[1]);
}

void Game::updateEvents(float deltaTime)
{
	while (this->window && this->window->pollEvent(this->ev)) {
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
	}
}
void Game::update()
{
	deltaTime = clock.restart().asSeconds();
	this->updateEvents(deltaTime);

	ballMovement();
	keyBoardInput();

	this->player1.setPosition(player1Pos[0], player1Pos[1]);
	this->player2.setPosition(player2Pos[0], player2Pos[1]);	
}

void Game::render()
{
	if (this->window) {
		this->window->clear(sf::Color(0, 0, 0, 0));

		this->window->draw(this->middleLine);
		this->window->draw(this->ball);
		this->window->draw(this->player1);
		this->window->draw(this->player2);
	
		this->window->draw(this->text1);
		this->window->draw(this->text2);

		this->window->display();
	}
}
