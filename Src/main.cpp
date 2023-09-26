#include <SFML/Graphics.hpp>
#include <assert.h>

#include "Widget/Flask/Flask.h"
#include "Particle/CircleParticle/CircleParticle.h"
#include "Particle/SquareParticle/SquareParticle.h"
#include "Widget/Button/Button.h"
#include "ButtonManager/ButtonManager.h"

const char kWindowHeader[] = "Sphere";
const int  kWindowSize     = 1000;
const int  kMaxTextLength  = 50;

int main()
{
    sf::RenderWindow window(sf::VideoMode(kWindowSize, kWindowSize), 
                            kWindowHeader);
	sf::Texture temp_up, temp_down;
	temp_up.loadFromFile("Resources/TempUp.png");
	temp_down.loadFromFile("Resources/TempDown.png");

	Widget background(0, 0, window.getSize().x, window.getSize().y, 5, sf::Color::Yellow);

	ButtonManager button_man;
	Button* add_square_button = new Button(150, 525, 100, 50, AddSquareParticle, 5, sf::Color::Cyan);
	Button* add_circle_button = new Button(25,  525, 100, 50, AddCircleParticle, 5, sf::Color::Cyan);
	button_man.AddButton(add_square_button);
	button_man.AddButton(add_circle_button);
	button_man.AddButton(new Button(275, 525, 100, 50, IncreaseTemperature, 5, sf::Color::Cyan, temp_up));
	button_man.AddButton(new Button(400, 525, 100, 50, DecreaseTemperature, 5, sf::Color::Cyan, temp_down));

	Button* pistol_up   = new Button(525, 150, 50, 100, DropPistole,  5, sf::Color::Cyan);
	Button* pistol_down = new Button(525, 275, 50, 100, RaisePistole, 5, sf::Color::Cyan);
	button_man.AddButton(pistol_up);
	button_man.AddButton(pistol_down);

    Flask flask(0, 0, 500, 500);

	sf::Text temperature;
	temperature.setPosition(sf::Vector2f(550, 50));
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

		sf::RectangleShape square(sf::Vector2f(25, 25));
		square.setFillColor(sf::Color::Green);
		square.setPosition(37.5, 12.5);
		add_square_button->DrawInside(square);

		sf::CircleShape circle(12.5);
		circle.setFillColor(sf::Color::Red);
		circle.setPosition(37.5, 12.5);
		add_circle_button->DrawInside(circle);

		sf::Text pistol;
		pistol.setFont(font);
		pistol.setPosition(14, 20);
		pistol.setCharacterSize(45);
		pistol.setString("V");
		

		pistol_down->DrawInside(pistol);
		pistol.rotate(180);
		pistol.setPosition(37, 70);
		pistol_up->DrawInside(pistol);

		background.Draw(&window);
		button_man.Draw(&window);
        flask.Draw(&window);

    	sprintf(text, "t = %.1lf", flask.CalcTemp());
		temperature.setString(text);

		window.draw(temperature);

		window.display();

		//int k = 0;
		//scanf("%c\n", &k);
    }
}