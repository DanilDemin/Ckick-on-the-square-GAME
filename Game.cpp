#include "Game.h";




void Game::initVariables()
{
	window = nullptr;


}

void Game::initWindow()
{	
	videoMode.height = 1080;
	videoMode.width = 1920;

	window = new sf::RenderWindow(videoMode,
		"First Game", sf::Style::Titlebar | sf::Style::Close);


    window->setFramerateLimit(90);


}

void Game::initEnemies()
{   
   /* enemy.setPosition()*/
    enemy.setSize(sf::Vector2f(100.f, 100.f));
    enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    enemy.setFillColor(sf::Color::Red);
    enemy.setOutlineColor(sf::Color::Green);
    enemy.setOutlineThickness(1.f);

}

Game::Game()
{
	initVariables();
	initWindow();
    initEnemies();
}


Game::~Game() 
{
	delete window;
}

const bool Game::running() const
{
	return window->isOpen();
}

void Game::pollEvents()
{
    //Event polling

    while (window->pollEvent(ev)) {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape) {
                window->close();
            }
            break;
        }

    }

}

void Game::Update()
{
    pollEvents();

    //Update mouse position
    // relative ti the screen
    /*std::cout << "Mouse pos: " 
        << sf::Mouse::getPosition().x 
        << " " << sf::Mouse::getPosition().y << '\n';*/
    // Relative ti the window
    std::cout << "Mouse pos: " 
        << sf::Mouse::getPosition(*window).x
        << " " << sf::Mouse::getPosition(*window).y << '\n';

}


void Game::Render()
{   
    /*
    * // Render game objects
        clear old frame
        render objs
        display frame in window
    */


    window->clear(sf::Color::Black);

    // draw game objects
    window->draw(enemy);


    window->display();

}