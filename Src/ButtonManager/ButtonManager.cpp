#include "ButtonManager.h"

ButtonManager::ButtonManager() :
buttons (DynArray<Button*>(0))
{}

void ButtonManager::AddButton(Button* button)
{
    buttons.PushBack(button);
}

void ButtonManager::Draw(sf::RenderWindow* window)
{
    for (int i = 0; i < buttons.GetLength(); i++)
        buttons[i]->Draw(window);
}

void ButtonManager::Click(sf::Event event, Flask* flask)
{
	double mouse_x = event.mouseButton.x;
	double mouse_y = event.mouseButton.y;
    
    for (int i = 0; i < buttons.GetLength(); i++)
    {
        if (buttons[i]->Inside_p(mouse_x, mouse_y))
            (*buttons[i]->on_click)(flask);
    }
}
