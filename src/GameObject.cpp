#include "GameObject.h"
#include <iostream>


GameObject::GameObject() : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), 
	IsSolid(false), Destroyed(false), frame_i(0) {

}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	:Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false),
	Destroyed(false),
	frame_i(0)
{	

}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, std::vector<Texture2D> sprites, glm::vec3 color, glm::vec2 velocity)
	:Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprites(sprites), IsSolid(false), 
	Destroyed(false), frame_i(0)
{	

}

void GameObject::Draw(SpriteRenderer& Renderer) {
	Renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

void GameObject::Animate(SpriteRenderer& Renderer, float dt) {
	Renderer.DrawSprite(this->Sprites.back(), this->Position, this->Size, this->Rotation, this->Color);
	// this->frame_i = (this->frame_i + 1) % this->Sprites.size();
}