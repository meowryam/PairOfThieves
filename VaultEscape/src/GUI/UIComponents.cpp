
#include "GUI/UIComponents.h"
#include "GUI/Renderer.h"

namespace vh
{
    // Convert an integer into a character array
    static void intToText(int number, char buffer[])
    {
        char digits[20];

        int count = 0;
        bool negative = number < 0;

        if (negative)
            number = -number;

        do
        {
            digits[count] = '0' + (number % 10);

            number = number / 10;

            count++;

        } while (number > 0);

        int index = 0;

        if (negative)
        {
            buffer[index] = '-';
            index++;
        }

        for (int i = count - 1; i >= 0; i--)
        {
            buffer[index] = digits[i];
            index++;
        }

        buffer[index] = '\0';
    }


    // ==============================
    // BUTTON
    // ==============================

    Button::Button()
        : m_label("BUTTON"), m_hovered(false)
    {
        m_shape.setSize({ 160.f, 45.f });
        m_shape.setFillColor(Theme::LeafGreen);
        m_shape.setOutlineColor(Theme::DeepJungle);
        m_shape.setOutlineThickness(3.f);
    }


    Button::Button(
        sf::Vector2f position,
        sf::Vector2f size,
        const char* label)
        : m_label(label), m_hovered(false)
    {
        m_shape.setPosition(position);
        m_shape.setSize(size);

        m_shape.setFillColor(Theme::LeafGreen);
        m_shape.setOutlineColor(Theme::DeepJungle);
        m_shape.setOutlineThickness(3.f);
    }


    void Button::setLabel(const char* label)
    {
        m_label = label;
    }


    void Button::setPosition(sf::Vector2f position)
    {
        m_shape.setPosition(position);
    }


    void Button::setHovered(bool hovered)
    {
        m_hovered = hovered;
    }


    bool Button::contains(sf::Vector2f point) const
    {
        return m_shape.getGlobalBounds().contains(point);
    }


    bool Button::wasClicked(
        const sf::Event& event,
        const sf::RenderWindow& window) const
    {
        const auto* mouseEvent =
            event.getIf<sf::Event::MouseButtonPressed>();

        if (mouseEvent == nullptr)
            return false;

        if (mouseEvent->button != sf::Mouse::Button::Left)
            return false;

        sf::Vector2f mousePosition =
            window.mapPixelToCoords(mouseEvent->position);

        return contains(mousePosition);
    }


    void Button::render(
        sf::RenderWindow& window,
        Renderer& renderer) const
    {
        sf::Vector2f position = m_shape.getPosition();

        // Draw button shadow for depth
        sf::RectangleShape shadow = m_shape;
        shadow.setPosition({ position.x + 3.f, position.y + 3.f });
        shadow.setFillColor(Theme::DeepJungle);
        shadow.setOutlineThickness(0.f);
        window.draw(shadow);

        // Draw main button
        sf::RectangleShape button = m_shape;

        if (m_hovered)
            button.setFillColor(Theme::Lime);
        else
            button.setFillColor(Theme::LeafGreen);

        window.draw(button);

        // Draw highlight on top-left for raised appearance
        sf::RectangleShape highlight;
        highlight.setSize({ m_shape.getSize().x - 6.f, 2.f });
        highlight.setPosition({ position.x + 3.f, position.y + 3.f });
        highlight.setFillColor(Theme::Bamboo);
        window.draw(highlight);

        renderer.drawText(
            window,
            m_label,
            { position.x + 12.f, position.y + 10.f },
            18,
            Theme::Parchment
        );
    }


    // ==============================
    // PANEL
    // ==============================

    Panel::Panel()
        : m_title("")
    {
    }


    Panel::Panel(
        sf::Vector2f position,
        sf::Vector2f size,
        sf::Color color,
        const char* title)
        : m_title(title)
    {
        m_shape.setPosition(position);
        m_shape.setSize(size);

        m_shape.setFillColor(color);
        m_shape.setOutlineColor(Theme::Bamboo);
        m_shape.setOutlineThickness(2.f);
    }


    void Panel::render(
        sf::RenderWindow& window,
        Renderer& renderer) const
    {
        window.draw(m_shape);

        sf::Vector2f position = m_shape.getPosition();

        renderer.drawText(
            window,
            m_title,
            { position.x + 15.f, position.y + 12.f },
            20,
            Theme::TreasureGold
        );
    }


    // ==============================
    // HUD
    // ==============================

    HUD::HUD()
        : m_alarm(0), m_score(0), m_steps(0)
    {
        m_background.setPosition({ 20.f, 20.f });
        m_background.setSize({ 440.f, 75.f });

        m_background.setFillColor(Theme::ForestGreen);
        m_background.setOutlineColor(Theme::Bamboo);
        m_background.setOutlineThickness(2.f);
    }


    void HUD::setStats(int alarm, int score, int steps)
    {
        m_alarm = alarm;
        m_score = score;
        m_steps = steps;
    }


    void HUD::render(
        sf::RenderWindow& window,
        Renderer& renderer) const
    {
        window.draw(m_background);

        sf::Vector2f position = m_background.getPosition();

        char alarmText[20];
        char scoreText[20];
        char stepsText[20];

        intToText(m_alarm, alarmText);
        intToText(m_score, scoreText);
        intToText(m_steps, stepsText);

        renderer.drawText(
            window, "ALARM",
            { position.x + 15.f, position.y + 15.f },
            16, Theme::Parchment
        );

        renderer.drawText(
            window, alarmText,
            { position.x + 15.f, position.y + 40.f },
            18, Theme::TreasureGold
        );

        renderer.drawText(
            window, "SCORE",
            { position.x + 150.f, position.y + 15.f },
            16, Theme::Parchment
        );

        renderer.drawText(
            window, scoreText,
            { position.x + 150.f, position.y + 40.f },
            18, Theme::TreasureGold
        );

        renderer.drawText(
            window, "STEPS",
            { position.x + 300.f, position.y + 15.f },
            16, Theme::Parchment
        );

        renderer.drawText(
            window, stepsText,
            { position.x + 300.f, position.y + 40.f },
            18, Theme::TreasureGold
        );
    }


    // ==============================
    // OPERATION PANEL
    // ==============================

    OperationPanel::OperationPanel()
    {
    }


    OperationPanel::OperationPanel(sf::Vector2f position)
        : m_panel(
            position,
            { 240.f, 330.f },
            Theme::ForestGreen,
            "OPERATIONS")
    {
        float x = position.x + 20.f;
        float y = position.y + 65.f;

        m_buttons[0] = Button({ x, y }, { 200.f, 45.f }, "Search");
        m_buttons[1] = Button({ x, y + 60.f }, { 200.f, 45.f }, "Insert");
        m_buttons[2] = Button({ x, y + 120.f }, { 200.f, 45.f }, "Delete");
        m_buttons[3] = Button({ x, y + 180.f }, { 200.f, 45.f }, "Range Query");
    }


    void OperationPanel::setButtonLabel(int index, const char* label)
    {
        if (index >= 0 && index < 4)
        {
            m_buttons[index].setLabel(label);
        }
    }


    Button* OperationPanel::getButton(int index)
    {
        if (index >= 0 && index < 4)
            return &m_buttons[index];

        return nullptr;
    }


    void OperationPanel::render(
        sf::RenderWindow& window,
        Renderer& renderer) const
    {
        m_panel.render(window, renderer);

        for (int i = 0; i < 4; i++)
        {
            m_buttons[i].render(window, renderer);
        }
    }


    // ==============================
    // EVENT LOG
    // ==============================

    EventLog::EventLog()
        : m_messageCount(0)
    {
    }


    EventLog::EventLog(sf::Vector2f position)
        : m_panel(
            position,
            { 350.f, 210.f },
            Theme::ForestGreen,
            "EVENT LOG"),
        m_messageCount(0)
    {
        clear();
    }


    void EventLog::addMessage(const char* message)
    {
        if (m_messageCount == 6)
        {
            // Remove the oldest message
            for (int i = 1; i < 6; i++)
            {
                for (int j = 0; j < 80; j++)
                {
                    m_messages[i - 1][j] = m_messages[i][j];
                }
            }

            m_messageCount = 5;
        }

        int i = 0;

        while (message[i] != '\0' && i < 79)
        {
            m_messages[m_messageCount][i] = message[i];

            i++;
        }

        m_messages[m_messageCount][i] = '\0';

        m_messageCount++;
    }


    void EventLog::clear()
    {
        m_messageCount = 0;

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 80; j++)
            {
                m_messages[i][j] = '\0';
            }
        }
    }


    void EventLog::render(
        sf::RenderWindow& window,
        Renderer& renderer) const
    {
        m_panel.render(window, renderer);

        for (int i = 0; i < m_messageCount; i++)
        {
            renderer.drawText(
                window,
                m_messages[i],
                { 885.f, 515.f + (i * 25.f) },
                15,
                Theme::Parchment
            );
        }
    }


    // ==============================
    // TOOLBAR
    // ==============================

    Toolbar::Toolbar()
    {
    }


    Toolbar::Toolbar(sf::Vector2f position)
        : m_panel(
            position,
            { 500.f, 75.f },
            Theme::ForestGreen,
            "CONTROLS")
    {
        float x = position.x + 145.f;
        float y = position.y + 15.f;

        m_buttons[0] = Button({ x, y }, { 80.f, 40.f }, "Play");
        m_buttons[1] = Button({ x + 90.f, y }, { 80.f, 40.f }, "Step");
        m_buttons[2] = Button({ x + 180.f, y }, { 90.f, 40.f }, "Replay");
        m_buttons[3] = Button({ x + 280.f, y }, { 90.f, 40.f }, "Reset");
    }


    Button* Toolbar::getButton(int index)
    {
        if (index >= 0 && index < 4)
            return &m_buttons[index];

        return nullptr;
    }


    void Toolbar::render(
        sf::RenderWindow& window,
        Renderer& renderer) const
    {
        m_panel.render(window, renderer);

        for (int i = 0; i < 4; i++)
        {
            m_buttons[i].render(window, renderer);
        }
    }
}
