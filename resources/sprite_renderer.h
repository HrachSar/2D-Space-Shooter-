//
// Created by pap on 6/27/24.
//

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "../shader/shader.h"
#include "../texture/texture.h"

class sprite_renderer {
public:
    sprite_renderer(shader& _shader);
    ~sprite_renderer();

    void DrawSprite(texture _texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
    shader _shader;
    unsigned int quadVAO;

    void InitRenderData();
};



#endif //SPRITE_RENDERER_H
