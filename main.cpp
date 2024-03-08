#include "gui.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SIMPLE GAME GUI PROTO", sf::Style::Default);
    sf::Font font;
    if (!font.loadFromFile("C:/WINDOWS/FONTS/ARIAL.TTF")) 
    {
        std::cout << "ERROR : font not found" << std::endl;
    }

    GUI gui(window, font);
    gui.run();

    return 0;
}
