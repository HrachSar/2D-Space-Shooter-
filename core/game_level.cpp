#include "game_level.h"

#include "../resources/resource_manager.h"
#include <sstream>
#include <fstream>
#include <GLFW/glfw3.h>

#include <random>
#include <iostream>
#include "player_object.h"

void game_level::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight, player_object* player) {
    this->Bricks.clear();
    this->Enemies.clear();

    unsigned int brickCode;
    unsigned int enemyCode;
    game_level level;
    std::string line;
    std::ifstream fstream(file);

    if(fstream) {
        if (getline(fstream, line)) {
            std::istringstream sstream(line);
            sstream >> enemyCode >> brickCode;
        }
    }

    this->Init(enemyCode, brickCode, levelWidth, levelHeight, player);
}

void game_level::Init(unsigned int enemyCode, unsigned int brickCode, unsigned int levelWidth, unsigned int levelHeight, player_object* player) {

    float brickWidth = 40.0f;
    float brickHeight = 40.0f;
    float enemyWidth = 50.0f;
    float enemyHeight = 50.0f;
    glm::vec2 brickSize = glm::vec2(brickWidth, brickHeight);
    glm::vec2 enemySize = glm::vec2(enemyWidth, enemyHeight);



    for(unsigned int i = 0; i < brickCode; i++) {

        float brickPosx = static_cast<float>(rand()) / static_cast<float>((RAND_MAX / 2.0f)) * levelHeight;
        float brickPosy = static_cast<float>(rand()) / static_cast<float>((RAND_MAX / 2.0f)) * levelHeight;
        glm::vec2 brickPos = glm::vec2(brickPosx, brickPosy);
        game_object obj(brickPos, brickSize, resource_manager::GetTexture("brick"), glm::vec3(1.0f));
        obj.IsSolid = true;
        this->Bricks.push_back(obj);
    }
    std::cout << std::endl;
    for(unsigned int j = 0; j < enemyCode; j++) {

        float enemyPosx = static_cast<float>(rand()) / static_cast<float>((RAND_MAX / 3.0f)) * levelWidth;
        float enemyPosy = static_cast<float>(rand()) / static_cast<float>((RAND_MAX / 3.0f)) * levelWidth;
        if(enemyPosx < 0.0f || enemyPosx > 1600.0f || enemyPosy < 0.0f || enemyPosy > 1200.0f) {
            enemyPosx = levelWidth;
            enemyPosy = levelHeight;
        }
        glm::vec2 enemyPos = glm::vec2(enemyPosx, enemyPosy);
        enemy_object obj(enemyPos, enemySize, glm::vec2(0.0f), resource_manager::GetTexture("enemy"));
        obj.IsSolid = true;
        this->Enemies.push_back(obj);
    }
}
void game_level::Draw(sprite_renderer &renderer) {
     for(game_object &brick : this->Bricks) {
        if(brick.IsSolid)
            brick.Draw(renderer);
    }
    for(enemy_object &enemy : this->Enemies) {
        if(!enemy.IsDead)
            enemy.Draw(renderer);
    }
}
