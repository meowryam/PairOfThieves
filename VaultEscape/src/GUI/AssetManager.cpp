
#include "GUI/AssetManager.h"

namespace vh
{
    // Constructor
    AssetManager::AssetManager()
    {
        m_textureCount = 0;
    }


    // Compare two strings
    bool AssetManager::sameName(
        const char* first,
        const char* second) const
    {
        int i = 0;

        while (first[i] != '\0' && second[i] != '\0')
        {
            if (first[i] != second[i])
                return false;

            i++;
        }

        return first[i] == second[i];
    }


    // Load a texture
    bool AssetManager::loadTexture(
        const char* name,
        const char* filePath)
    {
        if (name == nullptr || filePath == nullptr)
            return false;

        if (name[0] == '\0' || filePath[0] == '\0')
            return false;

        // Check whether this texture already exists
        for (int i = 0; i < m_textureCount; i++)
        {
            if (sameName(m_names[i], name))
            {
                if (!m_textures[i].loadFromFile(filePath))
                    return false;

                m_textures[i].setSmooth(false);

                return true;
            }
        }

        // Check available space
        if (m_textureCount >= MAX_TEXTURES)
            return false;

        // Check name length
        int length = 0;

        while (name[length] != '\0')
        {
            if (length >= 63)
                return false;

            length++;
        }

        // Load image from file
        if (!m_textures[m_textureCount].loadFromFile(filePath))
            return false;

        // Keep pixel art sharp
        m_textures[m_textureCount].setSmooth(false);

        // Store texture name
        for (int i = 0; i < length; i++)
        {
            m_names[m_textureCount][i] = name[i];
        }

        m_names[m_textureCount][length] = '\0';

        m_textureCount++;

        return true;
    }


    // Load all jungle demo assets
    bool AssetManager::loadJungleAssets()
    {
        bool allLoaded = true;

        // Main textures
        if (!loadTexture("tileset", "assets/images/tileset.png"))
            allLoaded = false;

        if (!loadTexture("hero", "assets/images/hero_explorer_sheet.png"))
            allLoaded = false;


        // Animated objects
        if (!loadTexture("campfire", "assets/images/camp_campfire_small_burn.png"))
            allLoaded = false;

        if (!loadTexture("butterfly", "assets/images/critter_butterfly_blue_flutter.png"))
            allLoaded = false;

        if (!loadTexture("waterfall", "assets/images/river_waterfall_narrow_flow.png"))
            allLoaded = false;

        if (!loadTexture("emerald", "assets/images/temple_gem_emerald_glint.png"))
            allLoaded = false;

        if (!loadTexture("spikeTrap", "assets/images/temple_spike_trap_cycle.png"))
            allLoaded = false;


        // Jungle props
        if (!loadTexture("backpack", "assets/images/camp_backpack.png"))
            allLoaded = false;

        if (!loadTexture("crate", "assets/images/camp_crate_stamped.png"))
            allLoaded = false;

        if (!loadTexture("tent", "assets/images/camp_tent_bell.png"))
            allLoaded = false;

        if (!loadTexture("bird", "assets/images/jungle_bird_of_paradise.png"))
            allLoaded = false;

        if (!loadTexture("bromeliad", "assets/images/jungle_bromeliad.png"))
            allLoaded = false;

        if (!loadTexture("flowers", "assets/images/jungle_flower_patch_magenta.png"))
            allLoaded = false;

        if (!loadTexture("mossyLog", "assets/images/jungle_log_mossy.png"))
            allLoaded = false;

        if (!loadTexture("mangoTree", "assets/images/jungle_mango_tree.png"))
            allLoaded = false;

        if (!loadTexture("mushroom", "assets/images/jungle_mushroom_giant_red.png"))
            allLoaded = false;

        if (!loadTexture("palmTree", "assets/images/jungle_palm_coconut_tall.png"))
            allLoaded = false;

        if (!loadTexture("mossyRock", "assets/images/jungle_rock_mossy.png"))
            allLoaded = false;

        if (!loadTexture("mangoBasket", "assets/images/outpost_basket_mangoes.png"))
            allLoaded = false;

        if (!loadTexture("hut", "assets/images/outpost_stilt_hut_small.png"))
            allLoaded = false;

        if (!loadTexture("canoe", "assets/images/river_canoe_paddles.png"))
            allLoaded = false;

        if (!loadTexture("crabPot", "assets/images/river_crab_pot.png"))
            allLoaded = false;

        if (!loadTexture("lilyPads", "assets/images/river_lily_pads_flowering.png"))
            allLoaded = false;

        if (!loadTexture("vineColumn", "assets/images/ruin_column_vine_wrapped.png"))
            allLoaded = false;

        if (!loadTexture("jaguar", "assets/images/ruin_guardian_jaguar.png"))
            allLoaded = false;

        if (!loadTexture("treasureChest", "assets/images/temple_chest_gold_closed.png"))
            allLoaded = false;

        if (!loadTexture("templeDoor", "assets/images/temple_door_guardian_face.png"))
            allLoaded = false;

        if (!loadTexture("clayPot", "assets/images/temple_pot_clay.png"))
            allLoaded = false;


        return allLoaded;
    }


    // Find texture using its name
    sf::Texture* AssetManager::getTexture(const char* name)
    {
        if (name == nullptr)
            return nullptr;

        for (int i = 0; i < m_textureCount; i++)
        {
            if (sameName(m_names[i], name))
            {
                return &m_textures[i];
            }
        }

        return nullptr;
    }


    // Return number of loaded textures
    int AssetManager::getTextureCount() const
    {
        return m_textureCount;
    }
}
