#include <HUD.h>

HUDElement::HUDElement(glm::vec2& pos, glm::vec2& size, Texture2D& texture, glm::vec2& rotation, glm::vec3& color) : 
    Position(pos), 
    Size(size), 
    Texture(texture),
    Rotation(rotation),
    Color(color) { 
}

HUDElement::Draw(SpriteRenderer* Renderer) {
    Renderer->DrawSprite(this->texture, this->Position, this->Size, this->Rotation, this->Color);
}