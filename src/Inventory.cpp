#include "Inventory.h";

Invetory::Inventory() {
    this->Items = std::unordered_map<uint32_t, InventoryItem>();
}

Inventory::Draw(SpriteRenderer* Renderer) {
    for (auto& [item_id, item]: this->Items) {
        item.Draw(Renderer);
    }
}

Inventory::AddItem(InventoryItem& item) {
    this->Items[item->id]  =item; 
}

Inventory::RemoveItem() {
    this->Items.erase(item->id);
}