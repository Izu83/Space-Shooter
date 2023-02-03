#include "Game.h"

Game::Game()
{
	this->init_vairables();
	this->init_window();

}
Game::~Game()
{
	delete this->window;
}

void Game::poll_events()
{
	// Event polling
	while (this->window->pollEvent(event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

void Game::update()
{
	this->poll_events();
}

void Game::render()
{
	this->window->clear(sf::Color(255, 153, 153));
	// Draw game objects



	this->window->display();
}

const bool Game::running() const
{
	return this->window->isOpen();
}



void Game::init_vairables()
{
	this->window = nullptr;
}
void Game::init_window()
{
	this->video_mode.height = 600;
	this->video_mode.width = 800;
	this->window = new sf::RenderWindow(this->video_mode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
}