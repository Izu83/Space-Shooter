#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

class Game
{
private:
	void init_vairables();
	void init_window();

	// Window
	sf::RenderWindow* window;
	sf::VideoMode video_mode;
	sf::Event event;

public:
	// Constructors & Destructors
	Game();
	virtual ~Game();
	// Functions
	void poll_events();
	void update();
	void render();
	const bool running() const;
};
