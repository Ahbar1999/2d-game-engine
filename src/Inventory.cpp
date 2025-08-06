#include "Inventory.h";

Invetory::Inventory() {
    this->Items = std::unordered_map<uint32_t, InventoryItem>();
}

Inventory::Draw(SpriteRenderer* Renderer) {
    for (auto& item: this->items) {
        item.Draw(Renderer);
    }
}

