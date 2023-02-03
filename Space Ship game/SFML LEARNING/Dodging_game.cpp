#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(400, 400), "Dodging Game");
    window.setFramerateLimit(60);

    sf::RectangleShape player(sf::Vector2f(50, 50));
    player.setFillColor(sf::Color::Green);
    player.setPosition(175, 325);

    std::vector<sf::RectangleShape> obstacles;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.move(5, 0);

        if (rand() % 100 == 0)
        {
            sf::RectangleShape obstacle(sf::Vector2f(50, 50));
            obstacle.setFillColor(sf::Color::Red);
            obstacle.setPosition(rand() % 300, 0);
            obstacles.push_back(obstacle);
        }

        for (int i = 0; i < obstacles.size(); i++)
        {
            obstacles[i].move(0, 5);

            if (obstacles[i].getGlobalBounds().intersects(player.getGlobalBounds()))
                window.close();
        }

        window.clear();
        window.draw(player);
        for (int i = 0; i < obstacles.size(); i++)
            window.draw(obstacles[i]);
        window.display();
    }

    return 0;
}