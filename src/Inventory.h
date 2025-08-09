#pragma once
#ifndef __INVENTORY_H_
#define __INVENTORY_H_

#include <unordered_map>
#include "InventoryItem.h"
#include "SpriteRenderer.h"

// add a way to draw all the items in an inventory together, like in a enclosing box 
// add support for equippable inventory items like character skin items
// add support for consumable inventory items like health items, powerups etc.
class Inventory :HUDElement {   
    Inventory();

    std::unordered_map<uint32_t, InventoryItem> Items;

    void Draw(SpriteRenderer* Renderer);

    void AddItem(InventoryItem& item);

    void RemoveItem();
};


#endif
