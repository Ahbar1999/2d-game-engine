#include "InventoryItem.h";

InventoryItem::InventoryItem(InventoryItem type, uint32_t count, ::vec2& position, glm::vec2& size, Texture2D& texture, glm::vec2& rotation, glm::vec3& color) 
    : Position(position),
    Size(size),
    Texture(texture),
    Rotation(rotation), 
    Color(color), 
    Type(type),
    Count(count) {
        this->id = rand() % 1000; 
}

InventoryItem::Draw(SpriteRenderer* Renderer) {
    Renderer->DrawSprite(this->Texture, this->Position, this->Size, this->Rotation, this->Color);
}