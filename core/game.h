//
// Created by pap on 6/27/24.
//

#ifndef GAME_H
#define GAME_H

#include "game_level.h"
#include "glm/glm.hpp"

enum GameState {
    GAME_ACITVE,
    GAME_MENU,
    GAME_WIN
};

class game {
public:
    GameState State;
    bool Keys[1024];
    unsigned int Width, Height;

    unsigned int Stage;
    std::vector<game_level> Stages;

    glm::mat4 ProjectionMatrix;
    glm::mat4 ViewMatrix;

    game(unsigned int width, unsigned int height);
    ~game();

    void Init();
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void DoCollisions(float dt);
    void ResetPlayer();
    void ProcessMouse(double xPosIn, double yPosIn);
    void ProcessCamera(float dt);
    static bool CheckCollisionsBetweenObjects(game_object& one, game_object& two);
private:
    glm::vec2 ScreenToWorld( float xPos, float yPos);
    glm::vec2 WorldToScreen(glm::vec2 position, glm::mat4 view, glm::mat4 projection);
};


#endif //GAME_H
