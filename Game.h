#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>



class Game {
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;


	// Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	sf::Font font;

	//Text

	sf::Text uiText;


	// Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	


	// Private Functons
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();

public:
	//Constructers and Destructors
	Game();
	virtual ~Game();


	//Accessors

	const bool running() const;
	const bool getEndGame() const;



	//Functions


	void spawnEnemy();

	void pollEvents();
	void UpdateMousePosition();
	void UpdateText();
	void UpdateEnemies();
	void Update();

	void RenderText(sf::RenderTarget& target);
	void RenderEnemies(sf::RenderTarget& target);
	void Render();


};