#pragma once

#include <iostream>

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


	//Game objects

	sf::RectangleShape enemy;
	


	// Private Functons
	void initVariables();
	void initWindow();
	void initEnemies();

public:
	//Constructers and Destructors
	Game();
	virtual ~Game();


	//Accessors

	const bool running() const;




	//Functions
	void pollEvents();
	void Update();
	void Render();

};