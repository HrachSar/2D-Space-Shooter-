//
// Created by pap on 7/1/24.
//

#include "player_object.h"

#include "../resources/resource_manager.h"

player_object::player_object() : game_object(), Health(MAX_HEALTH), IsShooting(false), LifeTime(LIFE_TIME){}
player_object::player_object(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, texture sprite) : game_object(pos, glm::vec2(size),
                                    sprite, glm::vec3(1.0f), velocity), Health(MAX_HEALTH), IsShooting(false), LifeTime(LIFE_TIME){}

void player_object::Reset(glm::vec2 position, glm::vec2 velocity) {
    this->Position = position;
    this->Velocity = velocity;
    this->IsSolid = true;
    this->Health = MAX_HEALTH;
    this->LifeTime = LIFE_TIME;
    this->Projectiles.clear();
}
void player_object::Shoot() {
        const glm::vec2 PROJECTILE_SIZE(20.0f, 20.0f);
        const float PROJECTILE_VELOCITY = 5.0f;
        glm::vec2 projectilePosition = this->Position + this->Size / 2.0f;
        glm::vec2 projectileVelocity = this->Direction * PROJECTILE_VELOCITY;

        texture projectileTexture = resource_manager::GetTexture("projectile");
        game_object* projectile = new game_object(projectilePosition, PROJECTILE_SIZE, projectileTexture,glm::vec3(1.0f), projectileVelocity);
        projectile->Rotation = this->Rotation;
        projectile->IsSolid = true;
        this->Projectiles.push_back(projectile);
}

void player_object::UpdateProjectiles(float dt) {
    for (auto projectile = Projectiles.begin(); projectile != Projectiles.end(); ) {
        (*projectile)->Position += (*projectile)->Velocity * dt;
        if (!(*projectile)->IsSolid) {
            delete *projectile;
            projectile = Projectiles.erase(projectile);
        } else {
        ++projectile;
        }
    }
}


