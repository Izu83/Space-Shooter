#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <Windows.h>

int main()
{

    int health{ 100 };
    int score{ 0 };

    sf::RenderWindow window(sf::VideoMode(800, 800), "Space Shooter");
    window.setFramerateLimit(60);

    sf::Image icon;
    if (!icon.loadFromFile("spaceCraft.png"))
        return 1;
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("spaceCraft.png"))
    {
        return 1;
    }
    sf::Sprite player;

    player.setTextureRect(sf::IntRect(0, 0, 128, 128));
    player.setTexture(playerTexture);
    player.setPosition(400.0f, 500.0f);
    double playerSpeed = 5;

    sf::Font font;
    font.loadFromFile("CascadiaCode.ttf");

    sf::Text score_t;
    score_t.setFont(font);
    score_t.setCharacterSize(24);
    score_t.setFillColor(sf::Color::White);

    std::vector<sf::RectangleShape> bullets;
    std::vector<sf::Sprite> enemies;

    sf::Texture enemy_texture;
    enemy_texture.loadFromFile("enemy.png");

    sf::Texture background_texture;
    background_texture.loadFromFile("background.jpg");
    sf::Sprite background{ background_texture };
    
    std::srand(time(NULL));

    while (window.isOpen())
    {
        score_t.setString("Score: " + std::to_string(score));

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (std::rand() % 25 == 0)
        {
            sf::Sprite enemy(enemy_texture);
            float x = std::rand() % (800 - 128);
            enemy.setPosition(x, -10.0f);
            enemies.push_back(enemy);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            sf::RectangleShape bullet(sf::Vector2f(2.0f, 5.0f));
            bullet.setFillColor(sf::Color::Yellow);
            bullet.setPosition(player.getPosition().x + playerTexture.getSize().x / 2.0f, player.getPosition().y);
            bullets.push_back(bullet);
        }

        for (int i = 0; i < bullets.size(); ++i)
        {
            if (bullets[i].getPosition().y < 0)
            {
                bullets.erase(bullets.begin() + i);
                --i;
            }
        }

        for (auto &enemy : enemies)
        {
            enemy.move(0.0f, 5.0f);
            if (enemy.getGlobalBounds().intersects(player.getGlobalBounds()))
            {
                sf::Text text;
                text.Bold;
                text.setCharacterSize(24);
                text.setFont(font);
                if (health <= 0)
                {
                    text.setString("You lost!");
                    text.setPosition(400, 400);
                    window.draw(text);
                    sf::sleep(sf::seconds(2));
                    window.close();
                }
                else
                    health--;

            }
        }

        for (auto &bullet : bullets)
        {
            bullet.move(0.0f, -5.0f);
            for (auto it = enemies.begin(); it != enemies.end(); ++it)
            {
                if (bullet.getGlobalBounds().intersects(it->getGlobalBounds()))
                {
                    if (health < 100)
                    {
                        health++;
                    }
                    score++;
                    enemies.erase(it);
                    break;
                }
            }
        }




        if (player.getPosition().x < 0)
        {
            player.setPosition(player.getPosition().x + 5, player.getPosition().y);
        }
        if (player.getPosition().x > 800 - 128)
        {
            player.setPosition(player.getPosition().x - 5, player.getPosition().y);
        }
        if (player.getPosition().y < 0)
        {
            player.setPosition(player.getPosition().x, player.getPosition().y + 5);
        }
        if (player.getPosition().y > 800 - 128)
        {
            player.setPosition(player.getPosition().x, player.getPosition().y - 5);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0, -playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0, playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-playerSpeed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(playerSpeed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();


        sf::Text health_t;
        health_t.Bold;
        health_t.setCharacterSize(24);
        health_t.setFont(font);
        health_t.setString("Health: " + std::to_string(health));
        health_t.setPosition(0, 30);

        window.clear();
        window.draw(background);
        window.draw(player);
        window.draw(score_t);
        window.draw(health_t);
        for (const auto& bullet : bullets)
        {
            window.draw(bullet);
        }
        for (const auto& enemy : enemies)
        {
            window.draw(enemy);
        }
        window.display();
    }

    return 0;
}

