
#pragma once

#include <SFML/Graphics.hpp>

namespace vh
{
    class AssetManager
    {
    private:

        static const int MAX_TEXTURES = 32;

        sf::Texture m_textures[MAX_TEXTURES];

        char m_names[MAX_TEXTURES][64];

        int m_textureCount;


        // Compare two names
        bool sameName(
            const char* first,
            const char* second
        ) const;


    public:

        AssetManager();

        // Load one texture
        bool loadTexture(
            const char* name,
            const char* filePath
        );

        // Load all jungle demo assets
        bool loadJungleAssets();

        // Find a texture using its name
        sf::Texture* getTexture(const char* name);

        // Get number of loaded textures
        int getTextureCount() const;
    };
}
