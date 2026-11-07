
#include "GUI/JungleScene.h"

#include "GUI/Renderer.h"
#include "GUI/Theme.h"

namespace vh
{
    // =====================================
    // CONSTRUCTOR
    // =====================================

    JungleScene::JungleScene(
        AssetManager& assets,
        Renderer& renderer)
        : m_assets(&assets),
        m_renderer(&renderer),
        m_player(assets),
        m_groundTile(nullptr),
        m_propCount(0),
        m_statusMessage("Choose the LEFT or RIGHT trail.")
    {
        // Initialise prop pointers
        for (int i = 0; i < MAX_PROPS; i++)
        {
            m_props[i] = nullptr;
        }


        // Background
        m_background.setSize({ 1280.f, 720.f });
        m_background.setFillColor(Theme::DeepJungle);


        // Get the jungle tileset
        sf::Texture* tileset = m_assets->getTexture("tileset");

        if (tileset != nullptr)
        {
            m_groundTile = new sf::Sprite(*tileset);

            // Each source tile is 16 x 16.
            // Display each tile at 3 times its original size.
            m_groundTile->setScale({ 3.f, 3.f });
        }


        // Horizontal trail
        m_horizontalPath.setPosition({ 300.f, 365.f });
        m_horizontalPath.setSize({ 680.f, 95.f });

        m_horizontalPath.setFillColor(Theme::WoodBrown);
        m_horizontalPath.setOutlineColor(Theme::DarkSoil);
        m_horizontalPath.setOutlineThickness(6.f);


        // Vertical trail
        m_verticalPath.setPosition({ 592.f, 410.f });
        m_verticalPath.setSize({ 96.f, 310.f });

        m_verticalPath.setFillColor(Theme::WoodBrown);
        m_verticalPath.setOutlineColor(Theme::DarkSoil);
        m_verticalPath.setOutlineThickness(6.f);


        // Three clearings:
        // Left, centre and right

        sf::Vector2f clearingPositions[3] =
        {
            { 385.f, 412.f },
            { 640.f, 412.f },
            { 875.f, 412.f }
        };

        for (int i = 0; i < 3; i++)
        {
            m_clearings[i].setRadius(52.f);

            m_clearings[i].setOrigin({ 52.f, 52.f });

            m_clearings[i].setPosition(clearingPositions[i]);

            m_clearings[i].setFillColor(Theme::WoodBrown);

            m_clearings[i].setOutlineColor(Theme::DarkSoil);

            m_clearings[i].setOutlineThickness(5.f);
        }


        // Left and right clickable trails
        m_leftPathArea = sf::FloatRect(
            { 300.f, 355.f },
            { 280.f, 115.f }
        );

        m_rightPathArea = sf::FloatRect(
            { 700.f, 355.f },
            { 280.f, 115.f }
        );


        // Starting position of the explorer
        m_player.setPosition({ 640.f, 412.f });


        // =================================
        // ADD JUNGLE PROPS
        // =================================

        addProp(
            "mangoTree",
            { 35.f, 65.f },
            2.3f
        );

        addProp(
            "palmTree",
            { 1110.f, 50.f },
            2.1f
        );

        addProp(
            "hut",
            { 1035.f, 510.f },
            2.0f
        );

        addProp(
            "flowers",
            { 300.f, 185.f },
            2.2f
        );

        addProp(
            "bromeliad",
            { 820.f, 170.f },
            2.4f
        );

        addProp(
            "mossyLog",
            { 330.f, 535.f },
            2.3f
        );

        addProp(
            "mushroom",
            { 760.f, 520.f },
            2.0f
        );

        addProp(
            "mossyRock",
            { 1020.f, 245.f },
            2.5f
        );

        addProp(
            "treasureChest",
            { 895.f, 340.f },
            2.8f
        );

        addProp(
            "vineColumn",
            { 75.f, 290.f },
            2.0f
        );

        addProp(
            "mangoBasket",
            { 470.f, 180.f },
            2.5f
        );

        addProp(
            "jaguar",
            { 1120.f, 290.f },
            2.0f
        );
    }



    // =====================================
    // DESTRUCTOR
    // =====================================

    JungleScene::~JungleScene()
    {
        delete m_groundTile;

        m_groundTile = nullptr;

        for (int i = 0; i < m_propCount; i++)
        {
            delete m_props[i];

            m_props[i] = nullptr;
        }
    }



    // =====================================
    // ADD PROPS
    // =====================================

    bool JungleScene::addProp(
        const char* textureName,
        sf::Vector2f position,
        float scale)
    {
        if (m_propCount >= MAX_PROPS)
            return false;

        sf::Texture* texture =
            m_assets->getTexture(textureName);

        if (texture == nullptr)
            return false;

        sf::Sprite* prop = new sf::Sprite(*texture);

        prop->setPosition(position);

        prop->setScale({ scale, scale });

        m_props[m_propCount] = prop;

        m_propCount++;

        return true;
    }



    // =====================================
    // DRAW GROUND
    // =====================================

    void JungleScene::drawGround(sf::RenderWindow& window)
    {
        // Always draw a fallback background
        window.draw(m_background);

        if (m_groundTile == nullptr)
            return;


        // Tile positions inside the original tileset.
        // These are grass/flower ground tiles.
        int tilePositions[4] =
        {
            0, 16, 32, 48
        };


        // Fill the window with grass tiles
        for (int y = 0; y < 720; y += 48)
        {
            for (int x = 0; x < 1280; x += 48)
            {
                int tileIndex =
                    ((x / 48) + (y / 48)) % 4;

                sf::IntRect source(
                    { tilePositions[tileIndex], 48 },
                    { 16, 16 }
                );

                m_groundTile->setTextureRect(source);

                m_groundTile->setPosition(
                    {
                        static_cast<float>(x),
                        static_cast<float>(y)
                    }
                );

                window.draw(*m_groundTile);
            }
        }
    }



    // =====================================
    // DIRT TRAIL HELPERS
    // =====================================

    // Add a rectangular section to the path map
    static void fillPathCells(
        bool path[23][40],
        int top,
        int bottom,
        int left,
        int right)
    {
        for (int row = top; row <= bottom; row++)
        {
            for (int col = left; col <= right; col++)
            {
                path[row][col] = true;
            }
        }
    }


    // Draw the complete tiled dirt trail
    static void drawTiledDirtTrail(
        sf::RenderWindow& window,
        sf::Texture* texture)
    {
        if (texture == nullptr)
            return;

        const int ROWS = 23;
        const int COLS = 40;

        const int TILE_SIZE = 16;
        const float TILE_SCALE = 2.f;
        const float CELL_SIZE = 32.f;

        // 0 = Grass
        // 1 = Dirt path
        bool path[ROWS][COLS] = {};


        // =================================
        // CREATE PATH NETWORK
        // =================================

        // Main horizontal trail
        fillPathCells(path, 11, 13, 6, 33);

        // Main vertical trail
        // Creates the central crossroads
        fillPathCells(path, 3, 19, 18, 20);

        // Upper-left turning branch
        fillPathCells(path, 7, 13, 10, 12);
        fillPathCells(path, 7, 9, 6, 12);

        // Lower-right turning branch
        fillPathCells(path, 11, 18, 29, 31);
        fillPathCells(path, 16, 18, 29, 37);


        // =================================
        // TILE SOURCE COORDINATES
        // =================================

        // Dirt interior variations
        const int dirtTiles[5] =
        {
            128, 144, 160, 224, 240
        };

        // Top grass-edge variations
        const int topEdges[5] =
        {
            48, 64, 80, 96, 112
        };

        // Bottom grass-edge variations
        const int bottomEdges[5] =
        {
            48, 64, 80, 96, 112
        };


        // Create one sprite and reuse it
        sf::Sprite tile(*texture);

        tile.setScale(
            { TILE_SCALE, TILE_SCALE }
        );

        tile.setOrigin(
            { 8.f, 8.f }
        );


        // =================================
        // DRAW EACH PATH CELL
        // =================================

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                // Skip grass cells
                if (!path[row][col])
                    continue;


                // Find exposed path edges

                // N = 1
                // E = 2
                // S = 4
                // W = 8

                int mask = 0;

                if (row == 0 || !path[row - 1][col])
                    mask |= 1;

                if (col == COLS - 1 || !path[row][col + 1])
                    mask |= 2;

                if (row == ROWS - 1 || !path[row + 1][col])
                    mask |= 4;

                if (col == 0 || !path[row][col - 1])
                    mask |= 8;


                // Choose a slightly different dirt texture
                // for neighbouring cells

                int variation = (row + col) % 5;

                int sourceX = dirtTiles[variation];
                int sourceY = 144;

                float rotation = 0.f;


                // =================================
                // STRAIGHT EDGES
                // =================================

                // Top edge
                if (mask == 1)
                {
                    sourceX = topEdges[variation];
                    sourceY = 112;
                }

                // Bottom edge
                else if (mask == 4)
                {
                    sourceX = bottomEdges[variation];
                    sourceY = 128;
                }

                // Right edge
                else if (mask == 2)
                {
                    sourceX = topEdges[variation];
                    sourceY = 112;

                    rotation = 90.f;
                }

                // Left edge
                else if (mask == 8)
                {
                    sourceX = topEdges[variation];
                    sourceY = 112;

                    rotation = 270.f;
                }


                // =================================
                // CORNER TILES
                // =================================

                // Top-left corner
                else if (mask == 9)
                {
                    sourceX = 0;
                    sourceY = 112;
                }

                // Top-right corner
                else if (mask == 3)
                {
                    sourceX = 240;
                    sourceY = 112;
                }

                // Bottom-left corner
                else if (mask == 12)
                {
                    sourceX = 0;
                    sourceY = 128;
                }

                // Bottom-right corner
                else if (mask == 6)
                {
                    sourceX = 240;
                    sourceY = 128;
                }


                // =================================
                // DRAW THE TILE
                // =================================

                sf::IntRect source(
                    { sourceX, sourceY },
                    { TILE_SIZE, TILE_SIZE }
                );

                tile.setTextureRect(source);

                tile.setRotation(


                    sf::degrees(rotation)
                );

                float x = col * CELL_SIZE + CELL_SIZE / 2.f;
                float y = row * CELL_SIZE + CELL_SIZE / 2.f;

                tile.setPosition({ x, y });

                window.draw(tile);
            }
        }
    }

    // =====================================
    // HANDLE EVENTS
    // =====================================

    void JungleScene::handleEvent(const sf::Event& event)
    {
        const auto* mouseEvent =
            event.getIf<sf::Event::MouseButtonPressed>();

        if (mouseEvent == nullptr)
            return;

        // Only respond to left clicks
        if (mouseEvent->button != sf::Mouse::Button::Left)
            return;

        // Don't select another trail while moving
        if (m_player.isMoving())
            return;

        sf::Vector2f mousePosition(
            static_cast<float>(mouseEvent->position.x),
            static_cast<float>(mouseEvent->position.y)
        );


        // LEFT TRAIL
        if (m_leftPathArea.contains(mousePosition))
        {
            m_player.moveTo({ 385.f, 412.f });

            m_statusMessage =
                "You chose the LEFT trail!";
        }


        // RIGHT TRAIL
        else if (m_rightPathArea.contains(mousePosition))
        {
            m_player.moveTo({ 875.f, 412.f });

            m_statusMessage =
                "You chose the RIGHT trail!";
        }
    }



    // =====================================
    // UPDATE
    // =====================================

    void JungleScene::update(float deltaTime)
    {
        m_player.update(deltaTime);
    }



    // =====================================
    // RENDER
    // =====================================

    void JungleScene::render(sf::RenderWindow& window)
    {
        // 1. Draw the existing jungle background
        drawGround(window);


        // 2. Draw the new tiled dirt trail
        sf::Texture* tileset =
            m_assets->getTexture("tileset");

        drawTiledDirtTrail(window, tileset);


        // 3. Draw jungle props above the trail
        for (int i = 0; i < m_propCount; i++)
        {
            if (m_props[i] != nullptr)
            {
                window.draw(*m_props[i]);
            }
        }


        // 4. Display trail labels
        m_renderer->drawText(
            window,
            "LEFT TRAIL - 30",
            { 325.f, 310.f },
            18,
            Theme::Parchment
        );

        m_renderer->drawText(
            window,
            "RIGHT TRAIL - 70",
            { 750.f, 310.f },
            18,
            Theme::Parchment
        );


        // 5. Display instructions
        m_renderer->drawText(
            window,
            "JUNGLE CROSSROADS",
            { 465.f, 145.f },
            28,
            Theme::TreasureGold
        );

        m_renderer->drawText(
            window,
            "Choose a trail to continue your adventure",
            { 390.f, 190.f },
            19,
            Theme::Parchment
        );


        // 6. Display status
        m_renderer->drawText(
            window,
            m_statusMessage,
            { 420.f, 555.f },
            18,
            Theme::TreasureGold
        );


        // 7. Draw player above everything
        m_player.render(window);
    }
}