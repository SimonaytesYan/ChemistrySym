#include <SFML/Graphics.hpp>

#include "Widget/Flask/Flask.h"
#include "Particle/CircleParticle/CircleParticle.h"
#include "Particle/SquareParticle/SquareParticle.h"
#include "Widget/Button/Button.h"
#include "ButtonManager/ButtonManager.h"

const char kWindowHeader[] = "Sphere";
const int  kWindowSize     = 800;

int main()
{
    sf::RenderWindow window(sf::VideoMode(kWindowSize, kWindowSize), 
                            kWindowHeader);

	sf::Texture texture;
	texture.loadFromFile("Resources/carbon.jpg");

	ButtonManager button_man;
	button_man.AddButton(new Button(25,  450, 100, 50, AddCircleParticle, 5, texture));
	button_man.AddButton(new Button(150, 450, 100, 50, AddSquareParticle, 5, texture));
	button_man.AddButton(new Button(275, 450, 100, 50, IncreaseTemperature, 5, texture));
	button_man.AddButton(new Button(400, 450, 100, 50, DecreaseTemperature, 5, texture));
	button_man.AddButton(new Button(525, 450, 100, 50, RaisePistole, 5, texture));
	button_man.AddButton(new Button(650, 450, 100, 50, DropPistole, 5, texture));

    Flask flask(0, 0, 525, 400);

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

		button_man.Draw(&window);
        flask.Draw(&window);
		window.display();

		//int k = 0;
		//scanf("%c\n", &k);
    }
}