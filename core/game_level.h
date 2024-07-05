#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>

#include "enemy_object.h"
#include "game_object.h"
#include "player_object.h"


class game_level {
public:
    std::vector<game_object> Bricks;
    std::vector<enemy_object> Enemies;
    game_level(){}

    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight, player_object* player);
    void Draw(sprite_renderer& renderer);
    bool IsCompleted();
private:
    void Init(unsigned int enemyCode, unsigned int brickCode, unsigned int levelWidth, unsigned int levelHeight, player_object* player);

};



#endif //GAME_LEVEL_H
