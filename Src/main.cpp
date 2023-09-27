#include <SFML/Graphics.hpp>
#include <assert.h>

#include "Stopwatch.h"
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
	button_man->AddButton(new Button(100,  525, 100, 50,  AddCircleParticle,   0, sf::Color::Cyan, textures[0]));
	button_man->AddButton(new Button(225, 525, 100, 50,  AddSquareParticle,   0, sf::Color::Cyan, textures[1]));
	button_man->AddButton(new Button(350, 525, 100, 50,  IncreaseTemperature, 0, sf::Color::Cyan, textures[2]));
	button_man->AddButton(new Button(475, 525, 100, 50,  DecreaseTemperature, 0, sf::Color::Cyan, textures[3]));
	button_man->AddButton(new Button(25, 25, 50,  100, DropPistole,         5, sf::Color::Cyan, textures[4]));
	button_man->AddButton(new Button(25, 150, 50,  100, RaisePistole,        5, sf::Color::Cyan, textures[5]));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(kWindowSize, kWindowSize), 
                            kWindowHeader);
	sf::Texture circle, square, temp_up, temp_down;

	circle.loadFromFile("Resources/circle.png");
	square.loadFromFile("Resources/square.png");
	temp_up.loadFromFile("Resources/hot.png");
	temp_down.loadFromFile("Resources/cold.png");

	Widget background(0, 0, window.getSize().x, window.getSize().y, 0);
	
	sf::Texture textures[6] = {circle, square, temp_up, temp_down, 
							  sf::Texture(), sf::Texture()};

	ButtonManager button_man;
	CreateButtons(&button_man, textures);

    Flask flask(100, 0, 500, 500);

	sf::Font font;
	font.loadFromFile("Resources/Font.ttf");

	Plot temp_plot(650, 0, 300, 300, 
				           50,  250, 
				           50,  50, 
				    Vector(5,   50), font, "Time (s)", "Temp (K)",
				    sf::Color(255, 128, 0));
	
	Plot square_plot(650, 325, 300, 300,
							   50, 250,
				               50,  50, 
				    	Vector(5,   50), font, "Time (s)", "Squares",
				    sf::Color(128, 255, 0));

	Plot circle_plot(650, 650, 300, 300,
							   50, 250,
				               50,  50, 
				    	Vector(5,   50), font, "Time (s)", "Circles",
				    sf::Color(255, 0, 50));


	int time   = 0;
	int time_i = 0;
	InitTimer();
	
	while (window.isOpen())
	{
		StartTimer();

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

		if (time > 1e6)
		{
			time_i++;

			temp_plot.AddPoint(Vector(time_i, flask.CalcTemp()));
			circle_plot.AddPoint(Vector(time_i, flask.CalcCircles()));
			square_plot.AddPoint(Vector(time_i, flask.CalcSquares()));
			time = 0;
		}

		temp_plot.Draw(&window);
		circle_plot.Draw(&window);
		square_plot.Draw(&window);

		window.display();
		
		StopTimer();

		time += GetTimerMicroseconds();
    }
}