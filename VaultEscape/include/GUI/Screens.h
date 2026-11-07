
#pragma once

#include <SFML/Graphics.hpp>
#include "GUI/AnimationController.h"
#include "GUI/Screen.h"
#include "GUI/UIComponents.h"
#include "GUI/JungleScene.h"
namespace vh
{
    class UIManager;
    class Renderer;


    // =====================================
    // MAIN MENU SCREEN
    // =====================================

    class MainMenuScreen : public Screen
    {
    private:

        UIManager* m_manager;
        Renderer* m_renderer;

        Button m_buttons[4];

    public:

        MainMenuScreen(UIManager& manager, Renderer& renderer);

        void handleEvent(const sf::Event& event) override;
        void update(float deltaTime) override;
        void render(sf::RenderWindow& window) override;
    };


    // =====================================
    // CAMPAIGN MAP SCREEN
    // =====================================

    class CampaignMapScreen : public Screen
    {
    private:

        UIManager* m_manager;
        Renderer* m_renderer;

        Button m_buttons[5];

    public:

        CampaignMapScreen(UIManager& manager, Renderer& renderer);

        void handleEvent(const sf::Event& event) override;
        void update(float deltaTime) override;
        void render(sf::RenderWindow& window) override;
    };


    // =====================================
    // LEVEL SCREEN
    // =====================================

    class LevelScreen : public Screen
    {
    private:

        UIManager* m_manager;
        Renderer* m_renderer;

        int m_actNumber;
        int m_levelNumber;
        JungleScene m_jungleScene;
        HUD m_hud;

        OperationPanel m_operations;
        EventLog m_eventLog;
        Toolbar m_toolbar;
        AnimationController m_animation; 
        Button m_backButton;

    public:

        LevelScreen(
            UIManager& manager,
            Renderer& renderer,
            int actNumber,
            int levelNumber
        );

        void handleEvent(const sf::Event& event) override;
        void update(float deltaTime) override;
        void render(sf::RenderWindow& window) override;
    };


    // =====================================
    // RESULT SCREEN
    // =====================================

    class ResultScreen : public Screen
    {
    private:

        UIManager* m_manager;
        Renderer* m_renderer;

        int m_actNumber;
        int m_levelNumber;

        Button m_buttons[3];

    public:

        ResultScreen(
            UIManager& manager,
            Renderer& renderer,
            int actNumber,
            int levelNumber
        );

        void handleEvent(const sf::Event& event) override;
        void update(float deltaTime) override;
        void render(sf::RenderWindow& window) override;
    };


    // =====================================
    // SANDBOX SCREEN
    // =====================================

    class SandboxScreen : public Screen
    {
    private:

        UIManager* m_manager;
        Renderer* m_renderer;

        OperationPanel m_operations;
        EventLog m_eventLog;

        Button m_backButton;

    public:

        SandboxScreen(UIManager& manager, Renderer& renderer);

        void handleEvent(const sf::Event& event) override;
        void update(float deltaTime) override;
        void render(sf::RenderWindow& window) override;
    };


    // =====================================
    // LEADERBOARD SCREEN
    // =====================================

    class LeaderboardScreen : public Screen
    {
    private:

        UIManager* m_manager;
        Renderer* m_renderer;

        Panel m_panel;
        Button m_backButton;

    public:

        LeaderboardScreen(UIManager& manager, Renderer& renderer);

        void handleEvent(const sf::Event& event) override;
        void update(float deltaTime) override;
        void render(sf::RenderWindow& window) override;
    };


    // =====================================
    // REPORT VIEW SCREEN
    // =====================================

    class ReportViewScreen : public Screen
    {
    private:

        UIManager* m_manager;
        Renderer* m_renderer;

        Panel m_panel;
        Button m_backButton;

    public:

        ReportViewScreen(UIManager& manager, Renderer& renderer);

        void handleEvent(const sf::Event& event) override;
        void update(float deltaTime) override;
        void render(sf::RenderWindow& window) override;
    };
}
