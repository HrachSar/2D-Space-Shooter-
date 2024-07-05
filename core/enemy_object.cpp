#include "enemy_object.h"
#include <iostream>
#include "../resources/resource_manager.h"

enemy_object::enemy_object() : game_object(), Health(ENEMY_MAX_HEALTH), IsDead(false){}
enemy_object::enemy_object(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, texture sprite) : game_object(pos, size,
                                    sprite, glm::vec3(1.0f), velocity), IsDead(false), Health(ENEMY_MAX_HEALTH){}

void enemy_object::Attack(player_object* player, float dt) {

    glm::vec2 playerCenter = player->Position + player->Size / 2.0f;
    glm::vec2 enemyCenter = this->Position + this->Size / 2.0f;

    glm::vec2 direction = playerCenter - enemyCenter;

    float distance = glm::length(direction);
    if(distance <= MIN_DISTANCE) {
        this->Position += direction * SPEED * dt;
        float rotation = atan2(-direction.x, direction.y);
        this->Rotation = glm::degrees(rotation);
    }
}
