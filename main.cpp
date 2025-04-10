#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream> 

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Car Racing");
    window.setFramerateLimit(60);

    std::srand(std::time(nullptr));

   
    sf::RectangleShape player(sf::Vector2f(50, 30));
    player.setFillColor(sf::Color::Yellow);
    player.setPosition(400 - 25, 550);
    float playerSpeed = 200.0f;

   
    sf::RectangleShape enemy(sf::Vector2f(50, 30));
    enemy.setFillColor(sf::Color::Red);
    enemy.setPosition(static_cast<float>(rand() % 750), -50);
    float enemySpeed = 150.0f;

    
    sf::Color roadColor(50, 50, 50);
    sf::Color lineColor(100, 100, 100);
    float lineWidth = 5.0f;

   
    int score = 0;
    sf::Font font;
    if (!font.loadFromFile("KOMIKAP_.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

   
    bool isGameOver = false;
    sf::Clock gameClock; 

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float dtSeconds = deltaTime.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (!isGameOver) {
           
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                player.move(-playerSpeed * dtSeconds, 0);
                if (player.getPosition().x < 0) {
                    player.setPosition(0, player.getPosition().y);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                player.move(playerSpeed * dtSeconds, 0);
                if (player.getPosition().x > window.getSize().x - player.getSize().x) {
                    player.setPosition(window.getSize().x - player.getSize().x, player.getPosition().y);
                }
            }

            
            enemy.move(0, enemySpeed * dtSeconds);
            if (enemy.getPosition().y > window.getSize().y) {
                enemy.setPosition(static_cast<float>(rand() % static_cast<int>(window.getSize().x - enemy.getSize().x)), -50);
            }

            
            if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
                isGameOver = true;
                std::cout << "Game Over! Final Score: " << score << std::endl;
            }

          
            score = static_cast<int>(gameClock.getElapsedTime().asSeconds()); 
            std::stringstream ss;
            ss << "Score: " << score;
            scoreText.setString(ss.str());

        } else {
           
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                isGameOver = false;
                player.setPosition(400 - 25, 550);
                enemy.setPosition(static_cast<float>(rand() % static_cast<int>(window.getSize().x - enemy.getSize().x)), -50);
                score = 0;
                gameClock.restart(); 
            }
        }

       
        window.clear(roadColor);

        for (int i = 0; i < 5; ++i) {
            sf::RectangleShape line(sf::Vector2f(lineWidth, window.getSize().y));
            line.setFillColor(lineColor);
            line.setPosition(window.getSize().x / 5.0f * i - lineWidth / 2.0f, 0);
            window.draw(line);
        }

        window.draw(player);
        window.draw(enemy);
        window.draw(scoreText); 

        if (isGameOver) {
            sf::Text gameOverText("Game Over!", font, 48);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(window.getSize().x / 2.0f - gameOverText.getLocalBounds().width / 2.0f,
                                     window.getSize().y / 2.0f - gameOverText.getLocalBounds().height / 2.0f);
            window.draw(gameOverText);

            sf::Text restartText("Press Space to Restart", font, 24);
            restartText.setFillColor(sf::Color::White);
            restartText.setPosition(window.getSize().x / 2.0f - restartText.getLocalBounds().width / 2.0f,
                                      window.getSize().y / 2.0f + 30);
            window.draw(restartText);
        }

        window.display();
    }

    return 0;
}