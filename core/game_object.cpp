#include "game_object.h"

game_object::game_object() : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f, 0.0f), Direction(0.0f, 0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Timer(TIMER) {}
game_object::game_object(glm::vec2 position, glm::vec2 size, texture sprite, glm::vec3 color, glm::vec2 velocity, glm::vec2 direction) : Position(position), Size(size),Rotation(0.0f), Sprite(sprite), Color(color), Velocity(velocity), Direction(direction), IsSolid(false), Timer(TIMER) {}

void game_object::Draw(sprite_renderer &renderer) {
    renderer.DrawSprite(Sprite, Position, Size, Rotation, Color);
}
void game_object::UpdateLifeTime(float dt) {
    this->Timer -= dt;

    if(this->Timer <= 0.0f) {
        this->IsSolid = false;
        this->Timer = TIMER;
    }
}
