#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "widget.hpp"
#include "button.hpp"


class Menu
{
    private:
        std::string m_menu_name;
        std::shared_ptr<sf::Font> m_font;

        std::vector<std::shared_ptr<Widget>> m_widgets;
        int m_selectedItemIndex;

    public:
        Menu(const std::string& _menu_name, float _width, float _height, std::shared_ptr<sf::Font> _font) :
            m_menu_name(_menu_name),
            m_font(_font),
            m_selectedItemIndex(0)
        {
            std::cout << "INFO - " << __FUNCTION__ << " - " << m_menu_name << " : successfully initialized." << std::endl;
        }


        std::string get_name() const
        {
            return m_menu_name;
        }


        void add_widget(std::shared_ptr<Widget> widget)
        {
            m_widgets.push_back(widget);
        }


        void handle_event(sf::Event event, sf::RenderWindow &window)
        {
            for (auto &widget : m_widgets)
            {
                widget->isClicked(event, window);
            }
        }


        const int getPressedItem()
        {
            return m_selectedItemIndex;
        }


        const std::vector<std::shared_ptr<Widget>>& get_widgets() const
        {
            return m_widgets;
        }


        void draw(sf::RenderWindow &window)
        {
            for (auto &widget : m_widgets)
            {
                widget->draw(window);
            }
        }


        void moveUp()
        {
            if (m_selectedItemIndex - 1 >= 0)
            {
                // If the selected widget is a button, change its color
                auto prevButton = std::dynamic_pointer_cast<Button>(m_widgets[m_selectedItemIndex]);
                if (prevButton)
                {
                    prevButton->setSelected(false);
                }

                m_selectedItemIndex--;

                // If the newly selected widget is a button, change its color
                auto nextButton = std::dynamic_pointer_cast<Button>(m_widgets[m_selectedItemIndex]);
                if (nextButton)
                {
                    nextButton->setSelected(true);
                }
            }
        }


        void moveDown()
        {
            if (m_selectedItemIndex + 1 < m_widgets.size())
            {
                // If the selected widget is a button, change its color
                auto prevButton = std::dynamic_pointer_cast<Button>(m_widgets[m_selectedItemIndex]);
                if (prevButton)
                {
                    prevButton->setSelected(false);
                }

                m_selectedItemIndex++;

                // If the newly selected widget is a button, change its color
                auto nextButton = std::dynamic_pointer_cast<Button>(m_widgets[m_selectedItemIndex]);
                if (nextButton)
                {
                    nextButton->setSelected(true);
                }
            }
        }

};


#endif // MENU_HPP