#pragma once 
#ifndef _HUD_H_
#define _HUD_H_

#include "Texture.h"
#include <glm.hpp>
#include "SpriteRenderer.h"

class HUDElement  {
public:
    HUDElement(glm::vec2& position, glm::vec2& size, Texture2D& texture, glm::vec2& rotation = glm:vec2(0, 0), glm::vec3& color = glm:vec3(1.0));

    // 2d object so we only need two dimensions to store position, size etc
    glm::vec2 Position: 
    glm::vec2 Size; // In pixels ? 
    glm::vec2 Rotation;
    glm::vec3 Color;

    Texture2D texture;

    void Draw(SpriteRenderer* Renderer);
};


#endif