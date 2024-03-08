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

        std::function<void()> m_action;

        sf::Color m_normal_color;
        sf::Color m_hover_color;
        sf::Color m_click_color;

        bool m_isSelected;
        bool m_isPressed;

    public:
        Button(uint16_t _pos_x, uint16_t _pos_y, uint16_t _width, uint16_t _height, 
                std::shared_ptr<sf::Font> _font, const std::string& _text, std::function<void()> _action) :
            m_action(_action),
            m_normal_color(UI_BUTTON_FILL_COLOR_NORMAL),
            m_hover_color(UI_BUTTON_FILL_COLOR_HOVER),
            m_click_color(UI_BUTTON_FILL_COLOR_CLICK),
            m_isSelected(false),
            m_isPressed(false)
        {
            m_button_rect.setPosition(sf::Vector2f(_pos_x, _pos_y));
            m_button_rect.setSize(sf::Vector2f(_width, _height));
            m_button_rect.setOutlineThickness(2);
            m_button_rect.setOutlineColor(sf::Color(UI_BUTTON_OUTLINE_COLOR));

            m_button_text.setFont(*_font);
            m_button_text.setString(_text);
            m_button_text.setCharacterSize(24);
            m_button_text.setFillColor(sf::Color::Black);
            m_button_text.setPosition(sf::Vector2f(_pos_x, _pos_y));
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


        bool isClicked(sf::Event event, sf::RenderWindow &window) override 
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (isHovered(window))
                    {
                        m_isPressed = true;
                        std::cout<< "Button clicked, executing action... " << std::endl;
                        m_button_rect.setFillColor(m_click_color);
                        executeAction();
                        return true;
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    m_isPressed = false;
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


};


#endif // BUTTON_HPP