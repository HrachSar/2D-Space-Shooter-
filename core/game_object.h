//
// Created by pap on 6/27/24.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/glm.hpp>
#include "../texture/texture.h"
#include "../resources/sprite_renderer.h"
const float TIMER = 1.5f;

class game_object {
public:
    glm::vec2 Position, Velocity, Size, Direction;
    glm::vec3 Color;
    float Rotation;
    bool IsSolid;
    float Timer;
    texture Sprite;

    game_object();
    game_object(glm::vec2 position, glm::vec2 size, texture sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f), glm::vec2 direction = glm::vec2(0.0f));
    virtual void Draw(sprite_renderer& renderer);
    void UpdateLifeTime(float dt);

};



#endif //GAME_OBJECT_H
