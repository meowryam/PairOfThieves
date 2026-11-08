
#include "GUI/Screens.h"

#include "GUI/UIManager.h"
#include "GUI/Renderer.h"

namespace vh
{
    // =====================================
    // HELPER FUNCTIONS
    // =====================================

    // Convert mouse coordinates into screen coordinates
    static sf::Vector2f convertMousePosition(sf::Vector2i position)
    {
        return sf::Vector2f(
            static_cast<float>(position.x),
            static_cast<float>(position.y)
        );
    }


    // Get mouse click position
    static bool getClickPosition(
        const sf::Event& event,
        sf::Vector2f& position)
    {
        const auto* mouseEvent =
            event.getIf<sf::Event::MouseButtonPressed>();

        if (mouseEvent == nullptr)
            return false;

        if (mouseEvent->button != sf::Mouse::Button::Left)
            return false;

        position = convertMousePosition(mouseEvent->position);

        return true;
    }


    // Update button hover states
    static bool getHoverPosition(
        const sf::Event& event,
        sf::Vector2f& position)
    {
        const auto* mouseEvent =
            event.getIf<sf::Event::MouseMoved>();

        if (mouseEvent == nullptr)
            return false;

        position = convertMousePosition(mouseEvent->position);

        return true;
    }


    // =====================================
    // MAIN MENU SCREEN
    // =====================================


    MainMenuScreen::MainMenuScreen(
        UIManager& manager,
        Renderer& renderer)
        : m_manager(&manager),
        m_renderer(&renderer)
    {
        // Campaign button
        m_buttons[0] = Button(
            { 829.f, 220.f },
            { 260.f, 48.f },
            "CAMPAIGN"
        );

        // Sandbox button
        m_buttons[1] = Button(
            { 829.f, 290.f },
            { 260.f, 48.f },
            "SANDBOX"
        );

        // Leaderboard button
        m_buttons[2] = Button(
            { 829.f, 360.f },
            { 260.f, 48.f },
            "LEADERBOARD"
        );

        // Report View button
        m_buttons[3] = Button(
            { 829.f, 430.f },
            { 260.f, 48.f },
            "REPORT VIEW"
        );
    }



    void MainMenuScreen::handleEvent(const sf::Event& event)
    {
        sf::Vector2f position;

        // Handle mouse hovering
        if (getHoverPosition(event, position))
        {
            for (int i = 0; i < 4; i++)
            {
                m_buttons[i].setHovered(
                    m_buttons[i].contains(position)
                );
            }
        }

        // Check for mouse click
        if (!getClickPosition(event, position))
            return;


        // CAMPAIGN
        if (m_buttons[0].contains(position))
        {
            m_manager->setScreen(
                new CampaignMapScreen(*m_manager, *m_renderer)
            );
        }

        // SANDBOX
        else if (m_buttons[1].contains(position))
        {
            m_manager->setScreen(
                new SandboxScreen(*m_manager, *m_renderer)
            );
        }

        // LEADERBOARD
        else if (m_buttons[2].contains(position))
        {
            m_manager->setScreen(
                new LeaderboardScreen(*m_manager, *m_renderer)
            );
        }

        // REPORT VIEW
        else if (m_buttons[3].contains(position))
        {
            m_manager->setScreen(
                new ReportViewScreen(*m_manager, *m_renderer)
            );
        }
    }



    void MainMenuScreen::update(float deltaTime)
    {
        (void)deltaTime;
    }



    void MainMenuScreen::render(sf::RenderWindow& window)
    {
        // =====================================
        // BACKGROUND DECORATION
        // =====================================
        sf::Texture* backgroundTexture =
            m_manager->getAssetManager()->getTexture("background");

        if (backgroundTexture != nullptr)
        {
            sf::Sprite background(*backgroundTexture);

            sf::Vector2u textureSize = backgroundTexture->getSize();
            sf::Vector2u windowSize = window.getSize();

            float scaleX = (float)windowSize.x / textureSize.x;
            float scaleY = (float)windowSize.y / textureSize.y;

            background.setScale({ scaleX, scaleY });

            window.draw(background);
        }
        AssetManager* assets = m_manager->getAssetManager();

        // Draw mango tree
        if (assets != nullptr)
        {
           


            // Draw explorer
            sf::Texture* heroTexture =
                assets->getTexture("hero");

            if (heroTexture != nullptr)
            {
                sf::Sprite hero(*heroTexture);

                hero.setTextureRect(
                    sf::IntRect(
                        { 0, 0 },
                        { 16, 32 }
                    )
                );

                hero.setOrigin({ 8.f, 30.f });

                hero.setScale({ 6.f, 6.f });

                hero.setPosition({ 390.f, 475.f });

                window.draw(hero);
            }


            // Draw treasure chest
            sf::Texture* chestTexture =
                assets->getTexture("treasureChest");

            if (chestTexture != nullptr)
            {
                sf::Sprite chest(*chestTexture);

                chest.setPosition({ 360.f, 565.f });

                chest.setScale({ 2.5f, 2.5f });

                window.draw(chest);
            }
        }


        // =====================================
        // GAME TITLE
        // =====================================

        // Title shadow for depth
        m_renderer->drawText(
            window,
            "VAULT HEIST",
            { 133.f, 113.f },
            62,
            Theme::DarkSoil
        );

        // Main title
        m_renderer->drawText(
            window,
            "VAULT HEIST",
            { 130.f, 110.f },
            62,
            Theme::TreasureGold
        );

        // Subtitle
        m_renderer->drawText(
            window,
            "THE JUNGLE ADVENTURE",
            { 155.f, 190.f },
            27,
            Theme::Lime
       
        );

      
        



        // =====================================
        // TILE-BASED WOODEN MENU BOARD
        // =====================================

        sf::Texture* tileset =
            assets->getTexture("tileset");

        // Draw a small shadow behind the board
        sf::RectangleShape boardShadow;
        boardShadow.setSize({ 416.f, 480.f });
        boardShadow.setPosition({ 751.f, 132.f });
        boardShadow.setFillColor(Theme::DarkSoil);
        window.draw(boardShadow);


        if (tileset != nullptr)
        {
            sf::Sprite boardTile(*tileset);

            boardTile.setScale({ 2.f, 2.f });

            // Board dimensions:
            // 14 columns x 16 rows
            // Each displayed tile is 32 x 32 pixels.

            for (int row = 0; row < 15; row++)
            {
                for (int col = 0; col < 13; col++)
                {

                    int sourceX = 16;
                    int sourceY = 1936;

                    // Use a different wooden tile around the edges
                    if (row == 0 || row == 14 ||
                        col == 0 || col == 12)
                    {
                        sourceX = 0;
                        sourceY = 1936;
                    }

                    boardTile.setTextureRect(
                        sf::IntRect(
                            { sourceX, sourceY },
                            { 16, 16 }
                        )
                    );

                    boardTile.setPosition(
                        {
                            751.f + col * 32.f,
                            120.f + row * 32.f
                        }
                    
                    );

                    window.draw(boardTile);
                }
            }
        }


        // Menu heading - improved visual hierarchy
        m_renderer->drawText(
            window,
            "CHOOSE YOUR ADVENTURE",
            { 815.f, 155.f },
            20,
            Theme::TreasureGold
        );

        // Decorative divider line - enhanced
        sf::RectangleShape dividerTop;
        dividerTop.setSize({ 260.f, 1.f });
        dividerTop.setPosition({ 829.f, 185.f });

     
        dividerTop.setFillColor(Theme::Bamboo);
        window.draw(dividerTop);

        // Divider bottom shadow for depth
        sf::RectangleShape dividerBot;
        dividerBot.setSize({ 260.f, 1.f });
        dividerBot.setPosition({ 829.f, 188.f });
        dividerBot.setFillColor(Theme::DeepJungle);
        window.draw(dividerBot);


        // =====================================
        // MENU BUTTONS
        // =====================================

        for (int i = 0; i < 4; i++)
        {
            m_buttons[i].render(window, *m_renderer, tileset);
        }


        // =====================================
        // FOOTER
        // =====================================

        m_renderer->drawText(
            window,
            "CREDITS",
            { 920.f, 555.f },
            16,
            Theme::Bamboo
        );

        m_renderer->drawText(
            window,
            "EXPLORE. DISCOVER. ESCAPE.",
            { 840.f, 585.f },
            13,
            Theme::Parchment
        );
    }


    // =====================================
    // CAMPAIGN MAP SCREEN
    // =====================================

    CampaignMapScreen::CampaignMapScreen(
        UIManager& manager,
        Renderer& renderer)
        : m_manager(&manager),
        m_renderer(&renderer)
    {
        m_buttons[0] = Button(
            { 440.f, 160.f }, { 400.f, 55.f }, "Act 1 - Blueprint Wing"
        );

        m_buttons[1] = Button(
            { 440.f, 245.f }, { 400.f, 55.f }, "Act 2 - Sorted Wing"
        );

        m_buttons[2] = Button(
            { 440.f, 330.f }, { 400.f, 55.f }, "Act 3 - Balanced Wing"
        );

        m_buttons[3] = Button(
            { 440.f, 415.f }, { 400.f, 55.f }, "Act 4 - Heap Fortress"
        );

        m_buttons[4] = Button(
            { 30.f, 620.f }, { 140.f, 45.f }, "Back"
        );
    }


    void CampaignMapScreen::handleEvent(const sf::Event& event)
    {
        sf::Vector2f position;

        if (getHoverPosition(event, position))
        {
            for (int i = 0; i < 5; i++)
            {
                m_buttons[i].setHovered(
                    m_buttons[i].contains(position)
                );
            }
        }

        if (!getClickPosition(event, position))
            return;

        for (int i = 0; i < 4; i++)
        {
            if (m_buttons[i].contains(position))
            {
                m_manager->setScreen(
                    new LevelScreen(
                        *m_manager,
                        *m_renderer,
                        i + 1,
                        1
                    )
                );

                return;
            }
        }

        if (m_buttons[4].contains(position))
        {
            m_manager->setScreen(
                new MainMenuScreen(*m_manager, *m_renderer)
            );
        }
    }


    void CampaignMapScreen::update(float deltaTime)
    {
        (void)deltaTime;
    }


    void CampaignMapScreen::render(sf::RenderWindow& window)
    {
        m_renderer->drawText(
            window,
            "CAMPAIGN MAP",
            { 430.f, 55.f },
            42,
            Theme::TreasureGold
        );

        m_renderer->drawText(
            window,
            "Choose your adventure",
            { 490.f, 110.f },
            20,
            Theme::Parchment
        );

        for (int i = 0; i < 5; i++)
        {
            m_buttons[i].render(window, *m_renderer);
        }
    }



    // =====================================
    // LEVEL SCREEN
    // =====================================

    LevelScreen::LevelScreen(
        UIManager& manager,
        Renderer& renderer,
        int actNumber,
        int levelNumber)
        : m_manager(&manager),
        m_renderer(&renderer),
        m_actNumber(actNumber),
        m_levelNumber(levelNumber),
        m_jungleScene(*manager.getAssetManager(), renderer),
        m_operations({ 25.f, 160.f }),
        m_eventLog({ 895.f, 480.f }),
        m_toolbar({ 390.f, 620.f }),
        m_backButton(
            { 20.f, 620.f },
            { 130.f, 45.f },
            "Back"
        )
    {
        m_hud.setStats(0, 1000, 0);
        m_animation.setTotalSteps(5);
        m_eventLog.addMessage("Welcome to the vault!");
        m_eventLog.addMessage("Choose an operation.");

        // Act 4 uses heap-specific operations
        if (m_actNumber == 4)
        {
            m_operations.setButtonLabel(0, "Build Heap");
            m_operations.setButtonLabel(1, "Heapify");
            m_operations.setButtonLabel(2, "Extract Max");
            m_operations.setButtonLabel(3, "Heap Sort");
        }
    }


    void LevelScreen::handleEvent(const sf::Event& event)
    {
        sf::Vector2f position;

        if (getHoverPosition(event, position))
        {
            m_backButton.setHovered(
                m_backButton.contains(position)
            );

            for (int i = 0; i < 4; i++)
            {
                m_operations.getButton(i)->setHovered(
                    m_operations.getButton(i)->contains(position)
                );

                m_toolbar.getButton(i)->setHovered(
                    m_toolbar.getButton(i)->contains(position)
                );
            }
        }
        m_jungleScene.handleEvent(event);
        if (!getClickPosition(event, position))
            return;

        // Back to campaign
        if (m_backButton.contains(position))
        {
            m_manager->setScreen(
                new CampaignMapScreen(*m_manager, *m_renderer)
            );

            return;
        }

        // Operation buttons
        for (int i = 0; i < 4; i++)
        {
            if (m_operations.getButton(i)->contains(position))
            {
                if (m_actNumber == 4)
                {
                    if (i == 0)
                        m_eventLog.addMessage("Build Heap selected");

                    else if (i == 1)
                        m_eventLog.addMessage("Heapify selected");

                    else if (i == 2)
                        m_eventLog.addMessage("Extract Max selected");

                    else if (i == 3)
                        m_eventLog.addMessage("Heap Sort selected");
                }
                else
                {
                    if (i == 0)
                        m_eventLog.addMessage("Search selected");

                    else if (i == 1)
                        m_eventLog.addMessage("Insert selected");

                    else if (i == 2)
                        m_eventLog.addMessage("Delete selected");

                    else if (i == 3)
                        m_eventLog.addMessage("Range Query selected");
                }

                return;
            }
        }


        // Toolbar buttons
        for (int i = 0; i < 4; i++)
        {
            if (m_toolbar.getButton(i)->contains(position))
            {
                // PLAY / PAUSE
                if (i == 0)
                {
                    m_animation.togglePlayPause();

                    if (m_animation.isPlaying())
                    {
                        m_eventLog.addMessage("Animation started");
                    }
                    else
                    {
                        m_eventLog.addMessage("Animation paused");
                    }
                }

                // STEP FORWARD
                else if (i == 1)
                {
                    m_animation.stepForward();

                    m_eventLog.addMessage("Next step");
                }

                // REPLAY
                else if (i == 2)
                {
                    m_animation.replay();

                    m_eventLog.addMessage("Replaying animation");
                }

                // RESET
                else if (i == 3)
                {
                    m_animation.reset();

                    m_eventLog.addMessage("Animation reset");
                }

                return;
            }
        }

    }
   

    
void LevelScreen::render(sf::RenderWindow& window)
{
    // Draw jungle environment first
    m_jungleScene.render(window);
    // Draw jungle background
   

    // Display current Act and Level
    char title[40];

    title[0] = 'A';
    title[1] = 'C';
    title[2] = 'T';
    title[3] = ' ';
    title[4] = '0' + m_actNumber;
    title[5] = ' ';
    title[6] = '-';
    title[7] = ' ';
    title[8] = 'L';
    title[9] = 'E';
    title[10] = 'V';
    title[11] = 'E';
    title[12] = 'L';
    title[13] = ' ';
    title[14] = '0' + m_levelNumber;
    title[15] = '\0';

    m_renderer->drawText(
        window,
        title,
        { 520.f, 45.f },
        28,
        Theme::TreasureGold
    );


    // Display animation progress
    char stepNumber[2];

    stepNumber[0] =
        '0' + m_animation.getCurrentStep();

    stepNumber[1] = '\0';

    m_renderer->drawText(
        window,
        "ANIMATION STEP:",
        { 520.f, 90.f },
        16,
        Theme::Parchment
    );

    m_renderer->drawText(
        window,
        stepNumber,
        { 680.f, 90.f },
        16,
        Theme::TreasureGold
    );

    m_renderer->drawText(
        window,
        "/ 5",
        { 695.f, 90.f },
        16,
        Theme::Parchment
    );


    // Draw game interface over the environment
    m_hud.render(window, *m_renderer);

    m_operations.render(window, *m_renderer);

    m_eventLog.render(window, *m_renderer);

    m_toolbar.render(window, *m_renderer);

    m_backButton.render(window, *m_renderer);
}


// Update Level Screen
void LevelScreen::update(float deltaTime)
{
    // Update jungle and player movement
    m_jungleScene.update(deltaTime);

    // Update animation controller
    m_animation.update(deltaTime);

    // Update Play/Pause button label
    if (m_animation.isPlaying())
    {
        m_toolbar.getButton(0)->setLabel("Pause");
    }
    else
    {
        m_toolbar.getButton(0)->setLabel("Play");
    }
}


    // =====================================
    // RESULT SCREEN
    // =====================================

    ResultScreen::ResultScreen(
        UIManager& manager,
        Renderer& renderer,
        int actNumber,
        int levelNumber)
        : m_manager(&manager),
        m_renderer(&renderer),
        m_actNumber(actNumber),
        m_levelNumber(levelNumber)
    {
        m_buttons[0] = Button(
            { 510.f, 330.f }, { 240.f, 50.f }, "Retry"
        );

        m_buttons[1] = Button(
            { 510.f, 400.f }, { 240.f, 50.f }, "Campaign Map"
        );

        m_buttons[2] = Button(
            { 510.f, 470.f }, { 240.f, 50.f }, "Main Menu"
        );
    }


    void ResultScreen::handleEvent(const sf::Event& event)
    {
        sf::Vector2f position;

        if (getHoverPosition(event, position))
        {
            for (int i = 0; i < 3; i++)
            {
                m_buttons[i].setHovered(
                    m_buttons[i].contains(position)
                );
            }
        }

        if (!getClickPosition(event, position))
            return;

        if (m_buttons[0].contains(position))
        {
            m_manager->setScreen(
                new LevelScreen(
                    *m_manager,
                    *m_renderer,
                    m_actNumber,
                    m_levelNumber
                )
            );
        }

        else if (m_buttons[1].contains(position))
        {
            m_manager->setScreen(
                new CampaignMapScreen(*m_manager, *m_renderer)
            );
        }

        else if (m_buttons[2].contains(position))
        {
            m_manager->setScreen(
                new MainMenuScreen(*m_manager, *m_renderer)
            );
        }
    }


    void ResultScreen::update(float deltaTime)
    {
        (void)deltaTime;
    }


    void ResultScreen::render(sf::RenderWindow& window)
    {
        m_renderer->drawText(
            window,
            "LEVEL COMPLETE!",
            { 400.f, 130.f },
            48,
            Theme::TreasureGold
        );

        m_renderer->drawText(
            window,
            "Your jungle adventure continues...",
            { 390.f, 230.f },
            23,
            Theme::Parchment
        );

        for (int i = 0; i < 3; i++)
        {
            m_buttons[i].render(window, *m_renderer);
        }
    }



    // =====================================
    // SANDBOX SCREEN
    // =====================================

    SandboxScreen::SandboxScreen(
        UIManager& manager,
        Renderer& renderer)
        : m_manager(&manager),
        m_renderer(&renderer),
        m_operations({ 30.f, 140.f }),
        m_eventLog({ 895.f, 465.f }),
        m_backButton(
            { 30.f, 620.f },
            { 130.f, 45.f },
            "Back"
        )
    {
        m_eventLog.addMessage("Welcome to Sandbox!");
        m_eventLog.addMessage("Choose an operation.");
    }


    void SandboxScreen::handleEvent(const sf::Event& event)
    {
        sf::Vector2f position;

        if (getHoverPosition(event, position))
        {
            m_backButton.setHovered(
                m_backButton.contains(position)
            );

            for (int i = 0; i < 4; i++)
            {
                m_operations.getButton(i)->setHovered(
                    m_operations.getButton(i)->contains(position)
                );
            }
        }

        if (!getClickPosition(event, position))
            return;

        if (m_backButton.contains(position))
        {
            m_manager->setScreen(
                new MainMenuScreen(*m_manager, *m_renderer)
            );

            return;
        }

        for (int i = 0; i < 4; i++)
        {
            if (m_operations.getButton(i)->contains(position))
            {
                m_eventLog.addMessage("Sandbox operation selected");
                return;
            }
        }
    }


    void SandboxScreen::update(float deltaTime)
    {
        (void)deltaTime;
    }


    void SandboxScreen::render(sf::RenderWindow& window)
    {
        m_renderer->drawText(
            window,
            "JUNGLE SANDBOX",
            { 460.f, 50.f },
            40,
            Theme::TreasureGold
        );

        m_operations.render(window, *m_renderer);
        m_eventLog.render(window, *m_renderer);
        m_backButton.render(window, *m_renderer);

        // Sample node
        m_renderer->drawCircle(
            window,
            { 610.f, 270.f },
            100.f,
            Theme::ForestGreen,
            Theme::TreasureGold
        );

        m_renderer->drawText(
            window,
            "TREE / HEAP",
            { 550.f, 265.f },
            20,
            Theme::Parchment
        );
    }



    // =====================================
    // LEADERBOARD SCREEN
    // =====================================

    LeaderboardScreen::LeaderboardScreen(
        UIManager& manager,
        Renderer& renderer)
        : m_manager(&manager),
        m_renderer(&renderer),
        m_panel(
            { 290.f, 150.f },
            { 700.f, 420.f },
            Theme::ForestGreen,
            "LEADERBOARD"
        ),
        m_backButton(
            { 30.f, 620.f },
            { 130.f, 45.f },
            "Back"
        )
    {
    }


    void LeaderboardScreen::handleEvent(const sf::Event& event)
    {
        sf::Vector2f position;

        if (getHoverPosition(event, position))
        {
            m_backButton.setHovered(
                m_backButton.contains(position)
            );
        }

        if (getClickPosition(event, position))
        {
            if (m_backButton.contains(position))
            {
                m_manager->setScreen(
                    new MainMenuScreen(*m_manager, *m_renderer)
                );
            }
        }
    }


    void LeaderboardScreen::update(float deltaTime)
    {
        (void)deltaTime;
    }


    void LeaderboardScreen::render(sf::RenderWindow& window)
    {
        m_panel.render(window, *m_renderer);
        m_backButton.render(window, *m_renderer);

        m_renderer->drawText(
            window,
            "No leaderboard entries yet.",
            { 440.f, 320.f },
            25,
            Theme::Parchment
        );
    }



    // =====================================
    // REPORT VIEW SCREEN
    // =====================================

    ReportViewScreen::ReportViewScreen(
        UIManager& manager,
        Renderer& renderer)
        : m_manager(&manager),
        m_renderer(&renderer),
        m_panel(
            { 280.f, 130.f },
            { 720.f, 450.f },
            Theme::ForestGreen,
            "PROJECT REPORT"
        ),
        m_backButton(
            { 30.f, 620.f },
            { 130.f, 45.f },
            "Back"
        )
    {
    }


    void ReportViewScreen::handleEvent(const sf::Event& event)
    {
        sf::Vector2f position;

        if (getHoverPosition(event, position))
        {
            m_backButton.setHovered(
                m_backButton.contains(position)
            );
        }

        if (getClickPosition(event, position))
        {
            if (m_backButton.contains(position))
            {
                m_manager->setScreen(
                    new MainMenuScreen(*m_manager, *m_renderer)
                );
            }
        }
    }


    void ReportViewScreen::update(float deltaTime)
    {
        (void)deltaTime;
    }


    void ReportViewScreen::render(sf::RenderWindow& window)
    {
        m_panel.render(window, *m_renderer);
        m_backButton.render(window, *m_renderer);

        m_renderer->drawText(
            window,
            "BENCHMARK VISUALISATION",
            { 440.f, 220.f },
            25,
            Theme::TreasureGold
        );

        // Sample bars
        m_renderer->drawRectangle(
            window,
            { 420.f, 390.f },
            { 80.f, 130.f },
            Theme::LeafGreen
        );

        m_renderer->drawRectangle(
            window,
            { 550.f, 330.f },
            { 80.f, 190.f },
            Theme::TreasureGold
        );

        m_renderer->drawRectangle(
            window,
            { 680.f, 270.f },
            { 80.f, 250.f },
            Theme::Lime
        );

        m_renderer->drawText(
            window,
            "Sample data only",
            { 470.f, 540.f },
            16,
            Theme::Parchment
        );
    }
}
