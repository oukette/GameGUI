#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include "SFML/System.hpp"
#include <iostream>
#include <string>
#include <cmath>

#include "menu.hpp"
#include "button.hpp"


class GUI
{
    private:
        sf::RenderWindow &m_window;
        std::shared_ptr<sf::Font> m_font;

        sf::View m_view;

        std::vector<sf::VideoMode> m_supportedResolutions;
        sf::VideoMode m_referenceResolution;
        unsigned int m_referenceFontSize;

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
            m_view(m_window.getDefaultView()),
            m_referenceFontSize(UI_TEXT_SIZE_GENERAL),
            m_mainMenu("Main Menu", 800, 600, m_font),
            m_playSubMenu("Play Menu", 800, 600, m_font),
            m_optionsSubMenu("Options Menu", 800, 600, m_font),
            m_creditsSubMenu("Credits Menu", 800, 600, m_font),
            m_exitSubMenu("Exit Menu", 800, 600, m_font),
            m_currentMenu(nullptr),
            m_previousMenu(nullptr),
            m_selectedIndex(0)
        {
            // INIT the vector of supported resolutions
            for (const auto& resolution : RESOLUTIONS)
            {
                m_supportedResolutions.push_back({resolution.first, resolution.second, 32}); // 32-bit depth is a common choice
            }

            // SET the reference resolution and font size
            m_referenceResolution = m_supportedResolutions.front();

            // INIT the menus
            init_menus();
            std::cout << "INFO - " << __FUNCTION__ << " - GUI successfully initialized." << std::endl;

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
                sf::Vector2f(200.0f, 100.0f), sf::Vector2f(200.0f, 50.0f), m_font, m_referenceFontSize, "Play", 
                [this] { setCurrentMenu(std::make_unique<Menu>(m_playSubMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));

            m_mainMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(200.0f, 200.0f), sf::Vector2f(200.0f, 50.0f), m_font, m_referenceFontSize, "Options", 
                [this] { setCurrentMenu(std::make_unique<Menu>(m_optionsSubMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));

            m_mainMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(200.0f, 300.0f), sf::Vector2f(200.0f, 50.0f), m_font, m_referenceFontSize, "Credits", 
                [this] { setCurrentMenu(std::make_unique<Menu>(m_creditsSubMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));

            m_mainMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(200.0f, 400.0f), sf::Vector2f(200.0f, 50.0f), m_font, m_referenceFontSize, "Exit", 
                [this] { setCurrentMenu(std::make_unique<Menu>(m_exitSubMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));
        }


        void init_play_menu()
        {
            m_playSubMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(200.0f, 100.0f), sf::Vector2f(200.0f, 50.0f), m_font, m_referenceFontSize, "Solo", 
                [this] { return; }));

            m_playSubMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(200.0f, 200.0f), sf::Vector2f(200.0f, 50.0f), m_font, m_referenceFontSize, "Host", 
                [this] { return; }));

            m_playSubMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(200.0f, 300.0f), sf::Vector2f(200.0f, 50.0f), m_font, m_referenceFontSize, "Join", 
                [this] { return; }));

            m_playSubMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(50.0f, 500.0f), sf::Vector2f(100.0f, 50.0f), m_font, m_referenceFontSize, "Back", 
                [this] { setCurrentMenu(std::move(m_previousMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));

        }

        void init_options_menu()
        {
            m_optionsSubMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(200.0f, 100.0f), sf::Vector2f(200.0f, 50.0f), m_font, m_referenceFontSize, "General", 
                [this] { return; }));

            m_optionsSubMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(200.0f, 200.0f), sf::Vector2f(200.0f, 50.0f), m_font, m_referenceFontSize, "Graphics", 
                [this] { return; }));

            m_optionsSubMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(200.0f, 300.0f), sf::Vector2f(200.0f, 50.0f), m_font, m_referenceFontSize, "Audio", 
                [this] { return; }));

            m_optionsSubMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(200.0f, 400.0f), sf::Vector2f(200.0f, 50.0f), m_font, m_referenceFontSize, "Control", 
                [this] { return; }));

            m_optionsSubMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(50.0f, 500.0f), sf::Vector2f(100.0f, 50.0f), m_font, m_referenceFontSize, "Back", 
                [this] { setCurrentMenu(std::move(m_previousMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));

        }


        void init_credits_menu()
        {
            // m_creditsSubMenu.addWidget(std::make_shared<Label>(200, 300, 200, 50, m_font, "Lead Designer"));
            // m_creditsSubMenu.addWidget(std::make_shared<Label>(200, 400, 200, 50, m_font, "Programmers"));
            // m_creditsSubMenu.addWidget(std::make_shared<Label>(200, 500, 200, 50, m_font, "Artists"));
            m_creditsSubMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(50.0f, 500.0f), sf::Vector2f(100.0f, 50.0f), m_font, m_referenceFontSize, "Back", 
                [this] { setCurrentMenu(std::move(m_previousMenu));
                        std::cout << "DEBUG - " << __FUNCTION__ << " - displaying " << m_currentMenu->get_name() << std::endl; }));
        }


        void init_exit_menu()
        {
            m_exitSubMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(400.0f, 350.0f), sf::Vector2f(150.0f, 50.0f), m_font, m_referenceFontSize, "Confirm", 
                [this] { m_window.close(); }));

            m_exitSubMenu.add_widget(std::make_shared<Button>(
                sf::Vector2f(100.0f, 350.0f), sf::Vector2f(150.0f, 50.0f), m_font, m_referenceFontSize, "Cancel", 
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


        void updateLayout()
        {

        }


        void updateFontSize(float scaleFactor)
        {

        }


        sf::VideoMode findClosestResolution(sf::Vector2u currentSize)
        {
            sf::VideoMode closestResolution;
            float minDistance = std::numeric_limits<float>::max();

            for (const auto& resolution : m_supportedResolutions)
            {
                float distance = std::sqrt(std::pow(resolution.width - currentSize.x, 2) + std::pow(resolution.height - currentSize.y, 2));
                if (distance < minDistance)
                {
                    minDistance = distance;
                    closestResolution = resolution;
                }
            }

            return closestResolution;
        }


        void draw()
        {
            // Clear the window
            m_window.clear(sf::Color(BACKGROUND_COLOR));

            // Set the view
            m_window.setView(m_view);

            // Display the current menu
            m_currentMenu->draw(m_window);

            // Display the window
            m_window.display();
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
                    else if (event.type == sf::Event::Resized)
                    {
                        sf::VideoMode closestResolution = findClosestResolution({event.size.width, event.size.height});
                        m_window.setSize(sf::Vector2u(closestResolution.width, closestResolution.height));
                        updateLayout();

                    }
                    else if (event.type == sf::Event::KeyPressed)
                    {
                        if (event.key.code == sf::Keyboard::Up)
                        {
                            m_currentMenu->nav_move_up();
                            m_selectedIndex = m_currentMenu->get_pressed_item();
                        }
                        else if (event.key.code == sf::Keyboard::Down)
                        {
                            m_currentMenu->nav_move_down();
                            m_selectedIndex = m_currentMenu->get_pressed_item();
                        }
                        else if (event.key.code == sf::Keyboard::Return) // 'Enter' key
                        {
                            executeSelectedAction();
                        }
                    }

                    // HANDLE events
                    m_currentMenu->handle_event(event, m_window);
                }

                // UPDATE the GUI display
                draw();
            }
        }
};


#endif // GUI_HPP
