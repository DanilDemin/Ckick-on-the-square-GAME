#include "Game.h";




void Game::initVariables()
{
	window = nullptr;

    // Game logic
    endGame = false;
    points = 0;
    health = 10;
    enemySpawnTimerMax = 20.f;
    enemySpawnTimer = enemySpawnTimerMax; 
    maxEnemies = 10;
    mouseHeld = false;

}

void Game::initWindow()
{	
	videoMode.height = 1080;
	videoMode.width = 1920;

	window = new sf::RenderWindow(videoMode,
		"First Game", sf::Style::Titlebar | sf::Style::Close);


    window->setFramerateLimit(90);


}

void Game::initFonts()
{
    if(font.loadFromFile("Fonts/Aller_Bd.ttf"))
    {
        std::cout << "Faild to load fonts" << '\n';
    }
}

void Game::initText()
{
    uiText.setFont(font);
    uiText.setCharacterSize(60);
    uiText.setFillColor(sf::Color::White);
    uiText.setString("NONE");
}

void Game::initEnemies()
{   
   /* enemy.setPosition()*/

    enemy.setSize(sf::Vector2f(150.f, 150.f));
    enemy.setFillColor(sf::Color::Red);
    /*enemy.setOutlineColor(sf::Color::Green);
    enemy.setOutlineThickness(1.f);*/

}

Game::Game()
{
	initVariables();
	initWindow();
    initFonts();
    initText();
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

const bool Game::getEndGame() const
{
    return endGame;
}


//Functions

void Game::spawnEnemy()
{
    /*
        return void

        Spawns enemies ans sets theier colors ans positions
        -Sets a random position
        -Sets a random color
        -Adds enemy to the vector
    */


    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
        0.f
    );


    // Randomize enemy type
    int type = rand() % 5;

    switch (type)
    {
    case 0:
        enemy.setSize(sf::Vector2f(50.f, 50.f));
        enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        enemy.setSize(sf::Vector2f(100.f, 100.f));
        enemy.setFillColor(sf::Color::Yellow);
        break;
    case 2:
        enemy.setSize(sf::Vector2f(150.f, 150.f));
        enemy.setFillColor(sf::Color::Yellow);
        break;
    case 3:
        enemy.setSize(sf::Vector2f(200.f, 200.f));
        enemy.setFillColor(sf::Color::Red);
        break;
    case 4:
        enemy.setSize(sf::Vector2f(250.f, 250.f));
        enemy.setFillColor(sf::Color::Cyan);
        break;
    default:
        enemy.setSize(sf::Vector2f(130.f, 130.f));
        enemy.setFillColor(sf::Color::Green);
        break;
    }
    

    //Spawn the enemy
    enemies.push_back(enemy);

    //Remove the enemy at end of screen


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

void Game::UpdateMousePosition()
{

    /*
        return void
        
        updates the mouse positions:
        - Mouse position relative to window (Vector2i)
    */

    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
        
}

void Game::UpdateText()
{   
    std::stringstream ss;

    ss << "Points: " << points << '\n'
        << "Health: " << health;


    uiText.setString(ss.str());
}

void Game::UpdateEnemies()
{   

    /*
        return void
        Updates the enemy spawn timer and spawns enemies
        when the total amount of enemies is smaller than the maximum.
        Moves the enemies downwards
        Remove the enemies at the edge of the screen // TODO
    */


    //Upadating the timer for enemy spawning
    if (enemies.size() < maxEnemies) {
       

         
        if (enemySpawnTimer >= enemySpawnTimerMax) {
            //spawn the enemy and reset the timer
            spawnEnemy();
            enemySpawnTimer = 0.f;
            /*std::cout << "spawn!";*/
        } else {
            /*std::cout << "sum";*/
            enemySpawnTimer += 1.f;
        }
    }


    // Moving and updating enemies
    for (int i = 0; i < enemies.size(); ++i)
    {
        bool deleted = false;

        enemies[i].move(0.f, 5.f);  

        if (enemies[i].getPosition().y > window->getSize().y)
        {
            enemies.erase(enemies.begin() + i);
            health -= 1;
            std::cout << "Health: " << health << '\n';
        }
    }

    //check if clicked upon
   
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {   
        if (mouseHeld == false)
        {
            mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < enemies.size() && deleted == false; i++)
            {
                if (enemies[i].getGlobalBounds().contains(mousePosView))
                {
                    //Gain points
                    if (enemies[i].getFillColor() == sf::Color::Magenta) {
                        points += 10.f;
                    }
                    else if (enemies[i].getFillColor() == sf::Color::Yellow) {
                        points += 7.f;
                    }
                    else if (enemies[i].getFillColor() == sf::Color::Yellow) {
                        points += 5.f;
                    }
                    else if (enemies[i].getFillColor() == sf::Color::Red) {
                        points += 3.f;
                    }
                    else if (enemies[i].getFillColor() == sf::Color::Cyan) {
                        points += 1.f;
                    }
                    else if (enemies[i].getFillColor() == sf::Color::Green) {
                        points += 2.f;
                    }
                    
                    std::cout << "Points: " << points << '\n';


                    //Delete the enemy
                    deleted = true;
                    enemies.erase(enemies.begin() + i);
                }
            }
        }
    }
    else {
        mouseHeld = false;
    }

}

void Game::Update()
{   


    pollEvents();

    if (endGame == false)
    {
        UpdateMousePosition();
        UpdateText();
        UpdateEnemies();
    }


    //End game condition
    if (health <= 0) { endGame = true; }



    
    /*std::cout << enemySpawnTimer << '\n';*/
    /*std::cout << enemies.size() << '\n';*/
;}


void Game::RenderText(sf::RenderTarget& target)
{
    target.draw(uiText);
}

void Game::RenderEnemies(sf::RenderTarget& target)
{
    //Rendering all the enemies
    for (auto& e : enemies) {
        target.draw(e);
    }
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
    RenderEnemies(*window);
    RenderText(*window);


    window->display();

}