
#pragma once

#include <SFML/Graphics.hpp>
#include "GUI/Theme.h"

namespace vh
{
    class Renderer;


    // ==============================
    // BUTTON
    // ==============================

    class Button
    {
    private:

        sf::RectangleShape m_shape;
        const char* m_label;

        bool m_hovered;

    public:

        Button();

        Button(
            sf::Vector2f position,
            sf::Vector2f size,
            const char* label
        );

        void setLabel(const char* label);
        void setPosition(sf::Vector2f position);
        void setHovered(bool hovered);

        bool contains(sf::Vector2f point) const;

        bool wasClicked(
            const sf::Event& event,
            const sf::RenderWindow& window
        ) const;

        void render(
            sf::RenderWindow& window,
            Renderer& renderer
        ) const;
    };


    // ==============================
    // PANEL
    // ==============================

    class Panel
    {
    private:

        sf::RectangleShape m_shape;
        const char* m_title;

    public:

        Panel();

        Panel(
            sf::Vector2f position,
            sf::Vector2f size,
            sf::Color color,
            const char* title
        );

        void render(
            sf::RenderWindow& window,
            Renderer& renderer
        ) const;
    };


    // ==============================
    // HUD
    // ==============================

    class HUD
    {
    private:

        sf::RectangleShape m_background;

        int m_alarm;
        int m_score;
        int m_steps;

    public:

        HUD();

        void setStats(int alarm, int score, int steps);

        void render(
            sf::RenderWindow& window,
            Renderer& renderer
        ) const;
    };


    // ==============================
    // OPERATION PANEL
    // ==============================

    class OperationPanel
    {
    private:

        Panel m_panel;

        Button m_buttons[4];

    public:

        OperationPanel();

        OperationPanel(sf::Vector2f position);

        void setButtonLabel(int index, const char* label);

        Button* getButton(int index);

        void render(
            sf::RenderWindow& window,
            Renderer& renderer
        ) const;
    };


    // ==============================
    // EVENT LOG
    // ==============================

    class EventLog
    {
    private:

        Panel m_panel;

        char m_messages[6][80];

        int m_messageCount;

    public:

        EventLog();

        EventLog(sf::Vector2f position);

        void addMessage(const char* message);

        void clear();

        void render(
            sf::RenderWindow& window,
            Renderer& renderer
        ) const;
    };


    // ==============================
    // TOOLBAR
    // ==============================

    class Toolbar
    {
    private:

        Panel m_panel;

        Button m_buttons[4];

    public:

        Toolbar();

        Toolbar(sf::Vector2f position);

        Button* getButton(int index);

        void render(
            sf::RenderWindow& window,
            Renderer& renderer
        ) const;
    };
}
