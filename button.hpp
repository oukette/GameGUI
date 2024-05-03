#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

#include "widget.hpp"
#include "constants.hpp"


class Button : public Widget
{
    private:
        sf::RectangleShape m_button_rect;
        sf::Text m_button_text;

        unsigned int m_initialFontSize;

        sf::Vector2f m_relativePosition;
        sf::Vector2f m_relativeSize;
        
        std::function<void()> m_action;

        sf::Color m_normal_color;
        sf::Color m_hover_color;
        sf::Color m_click_color;

        bool m_isSelected;
        bool m_isPressed;

    public:
        Button(const sf::Vector2f& _relativePosition, const sf::Vector2f& _relativeSize, 
                std::shared_ptr<sf::Font> _font, unsigned int _fontSize, const std::string& _text, std::function<void()> _action) :
            m_initialFontSize(_fontSize),
            m_relativePosition(_relativePosition),
            m_relativeSize(_relativeSize),
            m_action(_action),
            m_normal_color(UI_BUTTON_FILL_COLOR_NORMAL),
            m_hover_color(UI_BUTTON_FILL_COLOR_HOVER),
            m_click_color(UI_BUTTON_FILL_COLOR_CLICK),
            m_isSelected(false),
            m_isPressed(false)
        {
            m_button_rect.setPosition(m_relativePosition);
            m_button_rect.setSize(m_relativeSize);
            m_button_rect.setOutlineThickness(2);
            m_button_rect.setOutlineColor(sf::Color(UI_BUTTON_OUTLINE_COLOR));

            m_button_text.setFont(*_font);
            m_button_text.setString(_text);
            m_button_text.setCharacterSize(_fontSize);
            m_button_text.setFillColor(sf::Color::Black);
            m_button_text.setPosition(m_relativePosition.x + m_relativeSize.x/2 - m_button_text.getGlobalBounds().width/2, 
                                      m_relativePosition.y + m_relativeSize.y/2 - m_button_text.getGlobalBounds().height/2);
            std::cout<< "DEBUG - " << __FUNCTION__ << "Button <" << _text << "> initialized." << std::endl;
        }


        unsigned int getFontSize() const
        {
            return m_button_text.getCharacterSize();
        }


        void draw(sf::RenderWindow &window) override 
        {
            sf::Color fillColor = m_normal_color;
            if (isHovered(window) || m_isSelected)
            {
                fillColor = m_hover_color;
            }
            if (m_isPressed)
            {
                fillColor = m_click_color;
            }

            m_button_rect.setFillColor(fillColor);

            window.draw(m_button_rect);
            window.draw(m_button_text);
        }


        void setFillColor(const sf::Color &color)
        {
            m_button_rect.setFillColor(color);
        }


        void setFontSize(unsigned int fontSize)
        {
            m_button_text.setCharacterSize(fontSize);
        }


        bool isClicked(sf::Event event, sf::RenderWindow &window) override 
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (isHovered(window))
                    {
                        m_isPressed = true;
                        m_button_rect.setFillColor(m_click_color);
                        return false;
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (isHovered(window))
                    {
                        m_isPressed = false;
                        std::cout<< "Button clicked" << std::endl;
                        executeAction();
                        return true;
                    }
                }
            }

            return false;
        }


        void executeAction()
        {
            if (m_action)
            {
                m_action();
            }
        }


        bool isHovered(sf::RenderWindow& window)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            return m_button_rect.getGlobalBounds().contains(float(mousePos.x), float(mousePos.y));
        }


        void setSelected(bool selected)
        {
            m_isSelected = selected;
        }


        void setPressed(bool pressed)
        {
            m_isPressed = pressed;
        }


        void updatePositionAndSize(const sf::View& view, float scaleFactor)
        {

        }


};


#endif // BUTTON_HPP