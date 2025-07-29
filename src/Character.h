#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include <vector>



class Character: public GameObject {
public:
    // you would want to make this object specific
    enum CharacterState {
        IDLE,
        RUNNING,
        WALKING,
        ATTACK1,
        ATTACK2,
        ATTACK3,
        DEAD,
    };

	Character(glm::vec2 pos, glm::vec2 size, float animation_speed, glm::vec3 color=glm::vec3(1.0f), glm::vec2 velocity=glm::vec2(0.0f, 0.0f));
    void Animate(SpriteRenderer& Renderer, float dt);

    CharacterState state;
    std::vector<std::vector<Texture2D>*> animations;
    void change_state(CharacterState new_state);

private:
	float animation_speed;	// time in seconds
	float time_since;		// time since last animation 

    uint16_t frame_i;
};

#endif