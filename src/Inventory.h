#pragma once
#ifndef __INVENTORY_H_
#define __INVENTORY_H_

#include <unordered_map>
#include "InventoryItem.h"
#include "SpriteRenderer.h"


// add support for equippable inventory items like character skin items
// add support for consumable inventory items like health items, powerups etc.
class Invetory {
    Inventory();

    std::unordered_map<uint32_t, InventoryItem> Items;

    // calls draw methods for all Invetory Items  
    void Draw(SpriteRenderer* Renderer);

    void AddItem(InventoryItem& item) {
        this->Items[item->id]  =item; 
    }

    void RemoveItem() {
        this->Items.erase(item->id);
    }
};


#endif
