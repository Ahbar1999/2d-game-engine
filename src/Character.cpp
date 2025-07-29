#include "Character.h"
#include "ResourceManager.h"

// call the base class game object constructor and set the initial state to idle  
Character::Character(glm::vec2 pos, 
    glm::vec2 size, 
    // std::vector<Texture2D> sprites, 
    float animation_speed, 
    glm::vec3 color, 
    glm::vec2 velocity): GameObject(pos, size, color, velocity) {
        this->state = CharacterState::IDLE;
        this->animation_speed = animation_speed;
        this->frame_i =0;

        // load and store animatinos 
        ResourceManager::LoadTextures("../Assets/Sprite_Sheets/Player/Idle.png", 6, true, "Player_Idle");
        ResourceManager::LoadTextures("../Assets/Sprite_Sheets/Player/Walk.png", 8, true, "Player_Walk");
        ResourceManager::LoadTextures("../Assets/Sprite_Sheets/Player/Attack_1.png", 6, true, "Player_Attack1");
        ResourceManager::LoadTextures("../Assets/Sprite_Sheets/Player/Run.png", 8, true, "Player_Run");
        this->animations.push_back(ResourceManager::getAnimation("Player_Idle"));
        this->animations.push_back(ResourceManager::getAnimation("Player_Run"));
        this->animations.push_back(ResourceManager::getAnimation("Player_Walk"));
        this->animations.push_back(ResourceManager::getAnimation("Player_Attack1"));
}

void Character::Animate(SpriteRenderer& Renderer, float dt) {
	this->time_since += dt;
	if (this->time_since > this->animation_speed) {
		this->frame_i = (this->frame_i + 1) % (*this->animations[this->state]).size();
		this->time_since =0;
	}
	// std::cout << "time since: " << this->time_since << std::endl;
	Renderer.DrawSprite((*this->animations[this->state])[this->frame_i], this->Position, this->Size, this->Rotation, this->Color);
}

void Character::change_state(CharacterState new_state) {
    this->state = new_state;
    this->frame_i =0;
}