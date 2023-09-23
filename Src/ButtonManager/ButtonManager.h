#ifndef SYM_BUTTON_MANAGER
#define SYM_BUTTON_MANAGER

#include <SFML/Graphics.hpp>

#include "../Widget/Flask/Flask.h"
#include "../Widget/Button/Button.h"
#include "../DynArray.h"

class ButtonManager
{
    DynArray<Button*> buttons;

public:

    ButtonManager();

    void AddButton(Button* button);

    void Draw(sf::RenderWindow* window);
    void Click(sf::Event event, Flask* flask);
};

#endif //SYM_BUTTON_MANAGER