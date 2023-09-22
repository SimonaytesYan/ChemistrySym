#include <SFML/Graphics.hpp>

#include "Widget/Flask/Flask.h"
#include "Particle/CircleParticle/CircleParticle.h"
#include "Particle/SquareParticle/SquareParticle.h"

const char kWindowHeader[] = "Sphere";
const int  kWindowSize     = 800;

int main()
{
    sf::RenderWindow window(sf::VideoMode(kWindowSize, kWindowSize), 
                            kWindowHeader);


    Flask flask(0, 0, 800, 800);

	for (int i = 0; i < 15; i++)
	{
    	flask.AddParticle(new CircleParticle(Vector(rand() % 800, rand() % 800), 
											 Vector(0.5 - rand() / RAND_MAX, 0.5 - rand() / RAND_MAX), 
											 10));
	}

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
			}
		}

        window.clear();

        flask.Draw(&window);
		window.display();

		//int k = 0;
		//scanf("%c\n", &k);
    }
}