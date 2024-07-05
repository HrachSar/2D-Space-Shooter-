//
// Created by pap on 7/1/24.
//

#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H
#include "game_object.h"
#include <vector>

const float MAX_HEALTH = 100.0f;
const float LIFE_TIME = 0.3f;

class player_object : public game_object{
public:
    float Health;
    float LifeTime;
    bool IsShooting;
    std::vector<game_object*> Projectiles;

    player_object();
    player_object(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, texture sprite);
    void Shoot();
    void Reset(glm::vec2 position, glm::vec2 velocity);
    void UpdateProjectiles(float dt);
};



#endif //PLAYER_OBJECT_H
