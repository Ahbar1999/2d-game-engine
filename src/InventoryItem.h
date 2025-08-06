#pragma once
#ifndef _INVENTORY_ITEM_H_
#define _INVENTORY_ITEM_H_
#include <HUD.h>

enum InventoryType {
    Consumable, // powerups, health items etc. 
    Equippable  // weapons, character skins
}

// change this, inventory items dont have to be a hud element, example items like skins and powerups need to be picked from the world
// so we need to interact with them  
class InventoryItem: HUDElement {
    uint32_t Id;
    uint32_t Count; // plurality of this inventory item  
    InventoryType Type;

    // constructor
    InventoryItem(glm::vec2& position, glm::vec2& size, Texture2D& texture, glm::vec2& rotation = glm:vec2(0, 0), glm::vec3& color = glm:vec3(1.0)); 
};

#endif