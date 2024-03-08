#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include "SFML/System.hpp"
#include <iostream>
#include <string>

#include "menu.hpp"
#include "button.hpp"


class GUI
{
    private:
        sf::RenderWindow &m_window;
        std::shared_ptr<sf::Font> m_font;
        Menu m_mainMenu;
        Menu m_playSubMenu;
        Menu m_optionsSubMenu;
        Menu m_creditsSubMenu;
        Menu m_exitSubMenu;

        std::unique_ptr<Menu> m_currentMenu;
        std::unique_ptr<Menu> m_previousMenu;

        int m_selectedIndex;

    public:
        GUI(sf::RenderWindow &_window, sf::Font &_font) : 
            m_window(_window),
            m_font(std::make_shared<sf::Font>(_font)),
            m_mainMenu("Main Menu", 800, 600, m_font),
            m_playSubMenu("Play Menu", 800, 600, m_font),
            m_optionsSubMenu("Options Menu", 800, 600, m_font),
            m_creditsSubMenu("Credits Menu", 800, 600, m_font),
            m_exitSubMenu("Exit Menu", 800, 600, m_font),
            m_currentMenu(nullptr),
            m_previousMenu(nullptr),
            m_selectedIndex(0)
        {
            // INIT the menus
            init_menus();

            // INIT the currrent menu
            m_currentMenu = std::make_unique<Menu>(m_mainMenu);
            // m_previousMenu = std::make_unique<Menu>(m_currentMenu);
        }


        void init_menus()
        {
            init_main_menu();
            init_play_menu();
            init_options_menu();
            init_credits_menu();
            init_exit_menu();
        }


        void init_main_menu()
        {
            m_mainMenu.add_widget(std::make_shared<Button>(
                200, 100, 200, 50, m_font, "Play", 
                [this] { setCurrentMenu(std::make_unique<Menu>(m_playSubMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));

            m_mainMenu.add_widget(std::make_shared<Button>(
                200, 200, 200, 50, m_font, "Options", 
                [this] { setCurrentMenu(std::make_unique<Menu>(m_optionsSubMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));

            m_mainMenu.add_widget(std::make_shared<Button>(
                200, 300, 200, 50, m_font, "Credits", 
                [this] { setCurrentMenu(std::make_unique<Menu>(m_creditsSubMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));

            m_mainMenu.add_widget(std::make_shared<Button>(
                200, 400, 200, 50, m_font, "Exit", 
                [this] { setCurrentMenu(std::make_unique<Menu>(m_exitSubMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));
        }


        void init_play_menu()
        {
            m_playSubMenu.add_widget(std::make_shared<Button>(
                200, 100, 200, 50, m_font, "Solo", 
                [this] { return; }));

            m_playSubMenu.add_widget(std::make_shared<Button>(
                200, 200, 200, 50, m_font, "Host", 
                [this] { return; }));

            m_playSubMenu.add_widget(std::make_shared<Button>(
                200, 300, 200, 50, m_font, "Join", 
                [this] { return; }));

            m_playSubMenu.add_widget(std::make_shared<Button>(
                50, 500, 100, 50, m_font, "Back", 
                [this] { setCurrentMenu(std::move(m_previousMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));

        }

        void init_options_menu()
        {
            m_optionsSubMenu.add_widget(std::make_shared<Button>(
                200, 100, 200, 50, m_font, "General", 
                [this] { return; }));

            m_optionsSubMenu.add_widget(std::make_shared<Button>(
                200, 200, 200, 50, m_font, "Graphics", 
                [this] { return; }));

            m_optionsSubMenu.add_widget(std::make_shared<Button>(
                200, 300, 200, 50, m_font, "Audio", 
                [this] { return; }));

            m_optionsSubMenu.add_widget(std::make_shared<Button>(
                200, 400, 200, 50, m_font, "Control", 
                [this] { return; }));

            m_optionsSubMenu.add_widget(std::make_shared<Button>(
                50, 500, 100, 50, m_font, "Back", 
                [this] { setCurrentMenu(std::move(m_previousMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));

        }


        void init_credits_menu()
        {
            // m_creditsSubMenu.addWidget(std::make_shared<Label>(200, 300, 200, 50, m_font, "Lead Designer"));
            // m_creditsSubMenu.addWidget(std::make_shared<Label>(200, 400, 200, 50, m_font, "Programmers"));
            // m_creditsSubMenu.addWidget(std::make_shared<Label>(200, 500, 200, 50, m_font, "Artists"));
            m_creditsSubMenu.add_widget(std::make_shared<Button>(
                50, 500, 100, 50, m_font, "Back", 
                [this] { setCurrentMenu(std::move(m_previousMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));
        }


        void init_exit_menu()
        {
            m_exitSubMenu.add_widget(std::make_shared<Button>(
                400, 350, 150, 50, m_font, "Confirm", 
                [this] { m_window.close(); }));

            m_exitSubMenu.add_widget(std::make_shared<Button>(
                100, 350, 150, 50, m_font, "Cancel", 
                [this] { setCurrentMenu(std::move(m_previousMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));
        }


        void executeSelectedAction()
        {
            if (m_selectedIndex >= 0 && m_selectedIndex < m_currentMenu->get_widgets().size())
            {
                auto widget = m_currentMenu->get_widgets()[m_selectedIndex];
                if (auto button = std::dynamic_pointer_cast<Button>(widget))
                {
                    button->executeAction();
                }
            }
        }


        void setCurrentMenu(std::unique_ptr<Menu> newMenu)
        {
            m_previousMenu = std::move(m_currentMenu);
            m_currentMenu = std::move(newMenu);
            m_selectedIndex = 0;
        }


        void run()
        {
            while (m_window.isOpen())
            {
                sf::Event event;
                while (m_window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        m_window.close();
                    }
                    else if (event.type == sf::Event::KeyPressed)
                    {
                        if (event.key.code == sf::Keyboard::Up)
                        {
                            m_currentMenu->moveUp();
                            m_selectedIndex = m_currentMenu->getPressedItem();
                        }
                        else if (event.key.code == sf::Keyboard::Down)
                        {
                            m_currentMenu->moveDown();
                            m_selectedIndex = m_currentMenu->getPressedItem();
                        }
                        else if (event.key.code == sf::Keyboard::Return) // 'Enter' key
                        {
                            executeSelectedAction();
                        }

                    }

                    // HANDLE events
                    m_currentMenu->handle_event(event, m_window);
                }

                m_window.clear();
                m_currentMenu->draw(m_window);
                m_window.display();
            }
        }
};


#endif // GUI_HPP
