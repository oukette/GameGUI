#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/Graphics.hpp>
#include "SFML/System.hpp"


class Widget
{
    public:
        virtual void draw(sf::RenderWindow& window) = 0;
        virtual bool isClicked(sf::Event event, sf::RenderWindow& window) = 0;
        // virtual void updatePositionAndSize(const sf::VideoMode& referenceResolution, unsigned int width, unsigned int height) = 0;

};


#endif // WIDGET_HPP