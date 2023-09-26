#include <SFML/Graphics.hpp>
#include <assert.h>

#include "Widget/Flask/Flask.h"
#include "Particle/CircleParticle/CircleParticle.h"
#include "Particle/SquareParticle/SquareParticle.h"
#include "Widget/Button/Button.h"
#include "ButtonManager/ButtonManager.h"
#include "Widget/Plot/Plot.h"

const char kWindowHeader[] = "Sphere";
const int  kWindowSize     = 1000;
const int  kMaxTextLength  = 50;

void CreateButtons(ButtonManager* button_man, sf::Texture textures[6])
{
	button_man->AddButton(new Button(25,  525, 100, 50,  AddCircleParticle,   0, sf::Color::Cyan, textures[0]));
	button_man->AddButton(new Button(150, 525, 100, 50,  AddSquareParticle,   0, sf::Color::Cyan, textures[1]));
	button_man->AddButton(new Button(275, 525, 100, 50,  IncreaseTemperature, 0, sf::Color::Cyan, textures[2]));
	button_man->AddButton(new Button(400, 525, 100, 50,  DecreaseTemperature, 0, sf::Color::Cyan, textures[3]));
	button_man->AddButton(new Button(525, 150, 50,  100, DropPistole,         0, sf::Color::Cyan, textures[4]));
	button_man->AddButton(new Button(525, 275, 50,  100, RaisePistole,        0, sf::Color::Cyan, textures[5]));
}

void OutputCurrentTemp(sf::Text* temperature, Flask* flask)
{
	char text[kMaxTextLength] = {};
    sprintf(text, "t = %.2lf", flask->CalcTemp());
	temperature->setString(text);
}

void CreateTempCounter(sf::Text* temperature, sf::Font* font)
{
	temperature->setPosition(sf::Vector2f(50, 800));
	temperature->setFillColor(sf::Color::Cyan);
    temperature->setCharacterSize(45);

	assert(font->loadFromFile("Resources/Font.ttf"));
	temperature->setFont(*font);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(kWindowSize, kWindowSize), 
                            kWindowHeader);
	sf::Texture circle, square, temp_up, temp_down;

	circle.loadFromFile("Resources/circle.png");
	square.loadFromFile("Resources/square.png");
	temp_up.loadFromFile("Resources/TempUp.png");
	temp_down.loadFromFile("Resources/TempDown.png");

	Widget background(0, 0, window.getSize().x, window.getSize().y, 0);
	
	sf::Texture textures[6] = {circle, square, temp_up, temp_down, 
							  sf::Texture(), sf::Texture()};

	ButtonManager button_man;
	CreateButtons(&button_man, textures);

    Flask flask(0, 0, 500, 500);

	sf::Text temperature;
	sf::Font font;

	CreateTempCounter(&temperature, &font);
	OutputCurrentTemp(&temperature, &flask);

	Plot temp_plot(600, 0,   400, 400, 
				   50,  350, 1,  1, sf::Color(255, 128, 0));

	int time = 0;

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

		OutputCurrentTemp(&temperature, &flask);
		window.draw(temperature);

		if (time % 100 == 0)
		{
			temp_plot.AddPoint(Vector(time / 100, flask.CalcTemp()));
		}
		temp_plot.Draw(&window);


		window.display();

		time++;
		//int k = 0;
		//scanf("%c\n", &k);
    }
}