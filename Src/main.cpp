#include <SFML/Graphics.hpp>
#include <assert.h>

#include "Widget/Flask/Flask.h"
#include "Particle/CircleParticle/CircleParticle.h"
#include "Particle/SquareParticle/SquareParticle.h"
#include "Widget/Button/Button.h"
#include "ButtonManager/ButtonManager.h"

const char kWindowHeader[] = "Sphere";
const int  kWindowSize     = 800;
const int  kMaxTextLength  = 50;

int main()
{
    sf::RenderWindow window(sf::VideoMode(kWindowSize, kWindowSize), 
                            kWindowHeader);
	sf::Texture texture, circle, square;
	circle.loadFromFile("Resources/circle.png");
	square.loadFromFile("Resources/square.jpg");
	texture.loadFromFile("Resources/carbon.jpg");

	Widget background(0, 0, window.getSize().x, window.getSize().y, 0);

	ButtonManager button_man;
	button_man.AddButton(new Button(25,  525, 100, 50, AddCircleParticle,   5, sf::Color::Cyan, texture));
	button_man.AddButton(new Button(150, 525, 100, 50, AddSquareParticle,   5, sf::Color::Cyan, texture));
	button_man.AddButton(new Button(275, 525, 100, 50, IncreaseTemperature, 5, sf::Color::Cyan, texture));
	button_man.AddButton(new Button(400, 525, 100, 50, DecreaseTemperature, 5, sf::Color::Cyan, texture));
	button_man.AddButton(new Button(525, 50,  50, 100, DropPistole,         5, sf::Color::Cyan, texture));
	button_man.AddButton(new Button(525, 175, 50, 100, RaisePistole,        5, sf::Color::Cyan, texture));

    Flask flask(0, 0, 500, 500);

	sf::Text temperature;
	temperature.setPosition(sf::Vector2f(600, 50));
	temperature.setFillColor(sf::Color::Cyan);
    temperature.setCharacterSize(45);

	sf::Font font;
	assert(font.loadFromFile("Resources/Font.ttf"));
	temperature.setFont(font);

	char text[kMaxTextLength] = {};
    sprintf(text, "t = %lf", flask.CalcTemp());
	temperature.setString(text);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					window.close();
				}

				case sf::Event::MouseButtonPressed:
				{
					button_man.Click(event, &flask);
				}
			}
		}

        window.clear();

		background.Draw(&window);
		button_man.Draw(&window);
        flask.Draw(&window);

    	sprintf(text, "t = %.2lf", flask.CalcTemp());
		temperature.setString(text);

		window.draw(temperature);

		window.display();

		//int k = 0;
		//scanf("%c\n", &k);
    }
}