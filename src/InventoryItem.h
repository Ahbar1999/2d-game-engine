#pragma once
#ifndef _INVENTORY_ITEM_H_
#define _INVENTORY_ITEM_H_
#include <HUD.h>

enum InventoryType {
    Consumable, // powerups, health items etc. 
    Equippable  // weapons, character skins
}

class InventoryItem {
    uint32_t Id;
    uint32_t Count; // plurality of this inventory item  
    InventoryType Type;
    
    glm::vec2 Position;
    glm::vec2 Size; // In pixels ? 
    glm::vec2 Rotation;
    glm::vec3 Color;

    Texture2D Texture;

    // constructor
    InventoryItem(glm::vec2& position, glm::vec2& size, Texture2D& texture, glm::vec2& rotation = glm:vec2(0, 0), glm::vec3& color = glm:vec3(1.0)); 

    void Draw(SpriteRenderer* Renderer); 
};

#endif