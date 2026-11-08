
#include<iostream>
#include "GUI/AssetManager.h"
using namespace std;
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
       // Main textures
    


        if (!loadTexture("tileset", "assets/images/tileset.png"))
        {
            cout << "ERROR: Failed to load tileset.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded tileset.png" << endl;
        }



        if (!loadTexture("hero", "assets/images/hero_explorer_sheet.png"))
        {
            cout << "ERROR: Failed to load hero_explorer_sheet.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded hero_explorer_sheet.png" << endl;
        }

     







        // Main menu background
        if (!loadTexture("background", "assets/images/background.png"))
        {
            cout << "ERROR: Failed to load background.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded background.png" << endl;
        }




     
        if (!loadTexture("campfire", "assets/images/camp_campfire_small_burn.png"))
        {
            cout << "ERROR: Failed to load camp_campfire_small_burn.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded camp_campfire_small_burn.png" << endl;
        }



     

        if (!loadTexture("butterfly", "assets/images/critter_butterfly_blue_flutter.png"))
        {
            cout << "ERROR: Failed to load critter_butterfly_blue_flutter.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded critter_butterfly_blue_flutter.png" << endl;
        }


        if (!loadTexture("waterfall", "assets/images/river_waterfall_narrow_flow.png"))
        {
            cout << "ERROR: Failed to load river_waterfall_narrow_flow.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded river_waterfall_narrow_flow.png" << endl;
        }


   
        if (!loadTexture("emerald", "assets/images/temple_gem_emerald_glint.png"))
        {
            cout << "ERROR: Failed to load temple_gem_emerald_glint.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded temple_gem_emerald_glint.png" << endl;
        }


     


        if (!loadTexture("spikeTrap", "assets/images/temple_spike_trap_cycle.png"))
        {
            cout << "ERROR: Failed to load temple_spike_trap_cycle.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded temple_spike_trap_cycle.png" << endl;
        }


        // Jungle props
    



        if (!loadTexture("backpack", "assets/images/camp_backpack.png"))
        {
            cout << "ERROR: Failed to load camp_backpack.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded camp_backpack.png" << endl;
        }















        if (!loadTexture("crate", "assets/images/camp_crate_stamped.png"))
        {
            cout << "ERROR: Failed to loadcamp_crate_stamped.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded camp_crate_stamped.png" << endl;
        }










        if (!loadTexture("tent", "assets/images/camp_tent_bell.png"))
        {
            cout << "ERROR: Failed to load camp_tent_bell.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded camp_tent_bell.png" << endl;
        }











        if (!loadTexture("bird", "assets/images/jungle_bird_of_paradise.png"))
        {
            cout << "ERROR: Failed to load jungle_bird_of_paradise.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded jungle_bird_of_paradise.png" << endl;
        }









        if (!loadTexture("bromeliad", "assets/images/jungle_bromeliad.png"))
        {
            cout << "ERROR: Failed to load jungle_bromeliad.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded jungle_bromeliad.png" << endl;
        }










        if (!loadTexture("flowers", "assets/images/jungle_flower_patch_magenta.png"))
        {
            cout << "ERROR: Failed to load jungle_flower_patch_magenta.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded jungle_flower_patch_magenta.png" << endl;
        }










        if (!loadTexture("mossyLog", "assets/images/jungle_log_mossy.png"))
        {
            cout << "ERROR: Failed to load jungle_log_mossy.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded jungle_log_mossy.png" << endl;
        }








        if (!loadTexture("mangoTree", "assets/images/jungle_mango_tree.png"))
        {
            cout << "ERROR: Failed to load jungle_mango_tree.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded jungle_mango_tree.png" << endl;
        }













        if (!loadTexture("mushroom", "assets/images/jungle_mushroom_giant_red.png"))
        {
            cout << "ERROR: Failed to jungle_mushroom_giant_red.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded jungle_mushroom_giant_red.png" << endl;
        }









        if (!loadTexture("palmTree", "assets/images/jungle_palm_coconut_tall.png"))
        {
            cout << "ERROR: Failed to jungle_palm_coconut_tall.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded jungle_palm_coconut_tall.png" << endl;
        }











        if (!loadTexture("mossyRock", "assets/images/jungle_rock_mossy.png"))
        {
            cout << "ERROR: Failed to jungle_rock_mossy.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded jungle_rock_mossy.png" << endl;
        }




                if (!loadTexture("mangoBasket", "assets/images/outpost_basket_mangoes.png"))
        {
            cout << "ERROR: Failed to outpost_basket_mangoes.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded outpost_basket_mangoes.png" << endl;
        }









        if (!loadTexture("hut", "assets/images/outpost_stilt_hut_small.png"))
        {
            cout << "ERROR: Failed to outpost_stilt_hut_small.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded outpost_stilt_hut_small.png" << endl;
        }









        if (!loadTexture("canoe", "assets/images/river_canoe_paddles.png"))
        {
            cout << "ERROR: Failed to river_canoe_paddles.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded river_canoe_paddles.png" << endl;
        }













        if (!loadTexture("crabPot", "assets/images/river_crab_pot.png"))
        {
            cout << "ERROR: Failed to river_crab_pot.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded river_crab_pot.png" << endl;
        }













        if (!loadTexture("lilyPads", "assets/images/river_lily_pads_flowering.png"))
        {
            cout << "ERROR: Failed to river_lily_pads_flowering.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded river_lily_pads_flowering.png" << endl;
        }












        if (!loadTexture("vineColumn", "assets/images/ruin_column_vine_wrapped.png"))
        {
            cout << "ERROR: Failed to ruin_column_vine_wrapped.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded ruin_column_vine_wrapped.png" << endl;
        }












        if (!loadTexture("jaguar", "assets/images/ruin_guardian_jaguar.png"))
        {
            cout << "ERROR: Failed to ruin_guardian_jaguar.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded ruin_guardian_jaguar.png" << endl;
        }












        if (!loadTexture("treasureChest", "assets/images/temple_chest_gold_closed.png"))
        {
            cout << "ERROR: Failed to temple_chest_gold_closed.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded temple_chest_gold_closed.png" << endl;
        }

        










        if (!loadTexture("templeDoor", "assets/images/temple_door_guardian_face.png"))
        {
            cout << "ERROR: Failed to load temple_door_guardian_face.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded temple_door_guardian_face.png" << endl;
        }










    


        if (!loadTexture("clayPot", "assets/images/temple_pot_clay.png"))
        {
            cout << "ERROR: Failed to load temple_pot_clay.png" << endl;
            allLoaded = false;
        }
        else
        {
            cout << "SUCCESS: Loaded temple_pot_clay.png" << endl;
        }






















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
