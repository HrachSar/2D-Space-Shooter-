//
// Created by pap on 7/3/24.
//

#ifndef ENEMY_OBJECT_H
#define ENEMY_OBJECT_H
#include "game_object.h"
#include "player_object.h"

const float ENEMY_MAX_HEALTH = 100.0f;
const float SPEED = 1.2f;
const float MIN_DISTANCE = 500.0f;

class enemy_object : public game_object{
public:
    float Health;
    bool IsDead;

    enemy_object();
    enemy_object(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, texture sprite);
    void Attack(player_object* player, float dt);
};



#endif //ENEMY_OBJECT_H
