#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Track.h"

int main()
{
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("resources/background.png");
	sf::RectangleShape background(sf::Vector2f(2800, 950));
	background.setOrigin(sf::Vector2f(700, 950));
	background.setTexture(&backgroundTexture);

	sf::RenderWindow window(sf::VideoMode(1440, 900), "Outrun");
	Track track(sf::Vector2f(720, 975), 1540, 25);
	sf::Clock clock;

	int hill = 0;
	int curve = 0;

	track.addSection(100, 0, 100);

	for (int i = 0; i < 1000; i++)
	{
		hill = (sin((i * 5) * M_PI / 180.0) * 250);
		hill += 200;
		curve = (sin((i * 3) * M_PI / 180.0) * 100);
		track.addSection(3, curve, hill);
	}

	sf::Event evnt;

	while (window.isOpen())
	{

		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window.close();
		}

		if (clock.getElapsedTime().asSeconds() > 0.04)
		{
			clock.restart();

			track.advance();

			background.setPosition(sf::Vector2f(background.getPosition().x, track.getTrackHeight()));

			if (track.getCurrentCurve() > 0)
				background.move(sf::Vector2f(3, 0));
			else if (track.getCurrentCurve() < 0)
				background.move(sf::Vector2f(-3, 0));
		}

		window.clear();
		window.draw(background);
		track.draw(&window);
		window.display();

	}

	return 0;
}