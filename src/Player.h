#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "SpriteRenderer.h"
#include <vector>


class Player: public GameObject {
public:
    std::vector<Texture2D> textures; 

    void Draw(SpriteRenderer* Renderer);
};

#endif