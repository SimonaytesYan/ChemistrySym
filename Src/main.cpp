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

	flask.AddParticle(new SquareParticle(Vector(50, 50), Vector(0.1, 0.1), 10, 2));
	flask.AddParticle(new SquareParticle(Vector(400, 400), Vector(-0.1, -0.1), 10, 2));
	
	//for (int i = 0; i < 7; i++)
	//{
    //	flask.AddParticle(new CircleParticle(Vector(rand() % (int)flask.GetSize().GetX(), 
	//												rand() % (int)flask.GetSize().GetY()), 
	//										 Vector((0.5 - rand() / RAND_MAX) / 2, 
	//										 		(0.5 - rand() / RAND_MAX) / 2), 
	//										 10));
	//}

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