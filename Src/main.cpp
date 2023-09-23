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

	ButtonManager button_man;
	button_man.AddButton(new Button(500, 500, 50, 50, AddCircleParticle));
	button_man.AddButton(new Button(600, 600, 50, 50, AddSquareParticle));

    Flask flask(0, 0, 400, 400);

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