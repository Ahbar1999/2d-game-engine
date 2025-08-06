#include "InventoryItem.h";

InventoryItem::InventoryItem(InventoryItem type, uint32_t count, ::vec2& position, glm::vec2& size, Texture2D& texture, glm::vec2& rotation, glm::vec3& color) 
    : HUDElement(glm::vec2& position, glm::vec2& size, Texture2D& texture, glm::vec2& rotation, glm::vec3& color), 
    Type(type),
    Count(count) {
        this->id = rand() % 1000; 
}