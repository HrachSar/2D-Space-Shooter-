#include "game.h"
#include "../resources/resource_manager.h"
#include "../resources/sprite_renderer.h"

#include <GLFW/glfw3.h>

#include "game_object.h"
#include <iostream>

#include "game_level.h"
#include "player_object.h"

sprite_renderer* Renderer;
player_object* Player;
game_level stages[3];

const glm::vec2 PLAYER_SIZE = glm::vec2(25.0f, 25.0f);
const float PLAYER_VELOCITY = 500.0f;
const float SENSITIVITY = 1.0f;

game::game(unsigned int width, unsigned int height) : Width(width), Height(height), State(GAME_ACITVE), Keys() {}
game::~game() {}

void game::Init() {
    resource_manager::LoadShader("../shader/shader.vs", "../shader/shader.fs", nullptr,"sprite");
    this->ProjectionMatrix = glm::ortho(0.0f, static_cast<float>(Width), static_cast<float>(Height), 0.0f, -1.0f, 1.0f);
    resource_manager::GetShader("sprite").Use().SetInteger("image", 0);
    resource_manager::GetShader("sprite").SetMatrix4x4("projection",this->ProjectionMatrix);

    shader _shader = resource_manager::GetShader("sprite");
    Renderer = new sprite_renderer(_shader);

    resource_manager::LoadTexture("../gfx/background.png", true, "background");
    resource_manager::LoadTexture("../gfx/player.png", true, "player");
    resource_manager::LoadTexture("../gfx/projectile.png", true, "projectile");
    resource_manager::LoadTexture("../gfx/brick.png", true, "brick");
    resource_manager::LoadTexture("../gfx/enemy.png", true, "enemy");

    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    texture playerTexture = resource_manager::GetTexture("player");
    Player = new player_object(playerPos, PLAYER_SIZE, glm::vec2(0.0f),playerTexture);

    stages[0].Load("../stages/stage01", this->Width, this->Height, Player);
    stages[1].Load("../stages/stage02", this->Width, this->Height, Player);
    stages[2].Load("../stages/stage03", this->Width, this->Height, Player);
    this->Stage = 0;
    this->Stages.push_back(stages[this->Stage]);


}
void game::Update(float dt) {
    if(Player->IsSolid) {
        for(auto projectile : Player->Projectiles)
            projectile->UpdateLifeTime(dt);
        Player->Color = glm::vec3(1.0f);
        Player->UpdateProjectiles(dt);
    }
    for(unsigned int i = 0; i < this->Stages[Stage].Enemies.size(); i++) {
        this->Stages[Stage].Enemies[i].Attack(Player, dt);
        if(this->Stages[Stage].Enemies[i].Health <= 0.0f) {
            this->Stages[Stage].Enemies[i].IsDead = true;
            this->Stages[Stage].Enemies.erase(this->Stages[Stage].Enemies.begin() + i);
        }
    }
    if(Player->Health <= 0.0f)
        Player->IsSolid = false;
    if(this->Stages[Stage].Enemies.empty()) {
        if(this->Stage < 2) {
            this->Stage++;
            this->Stages.push_back(stages[Stage]);
        }else {
            this->Stage = 0;
            this->Stages.push_back(stages[Stage]);
        }
        std::cout << this->Stage << std::endl;
    }
}

bool game::CheckCollisionsBetweenObjects(game_object &one, game_object &two) {
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x && two.Position.x + two.Size.x >= one.Position.x;
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y && two.Position.y + two.Size.y >= one.Position.y;

    return collisionX && collisionY;
}


void game::Render() {
    if(this->State == GAME_ACITVE) {
        texture backgroung = resource_manager::GetTexture("background");
        Renderer->DrawSprite(backgroung, glm::vec2(0.0f), glm::vec2(this->Width, this->Height), 0.0f);
        Renderer->DrawSprite(backgroung, glm::vec2(800.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
        Renderer->DrawSprite(backgroung, glm::vec2(0.0f, 600.0f), glm::vec2(this->Width, this->Height), 0.0f);
        Renderer->DrawSprite(backgroung, glm::vec2(800.0f, 600.0f), glm::vec2(this->Width, this->Height), 0.0f);

        Player->Draw(*Renderer);
        this->Stages[Stage].Draw(*Renderer);
            for(auto projectile : Player->Projectiles) {
                if(projectile->IsSolid)
                    projectile->Draw(*Renderer);
            }


    }
}
void game::ProcessInput(float dt) {
    if(this->State == GAME_ACITVE && Player->IsSolid) {
        float velocity = PLAYER_VELOCITY * dt;
        if(this->Keys[GLFW_KEY_W]) {
            Player->Position.y -=  velocity;
        }
        if(this->Keys[GLFW_KEY_S]) {
            Player->Position.y += velocity;
        }
        if(this->Keys[GLFW_KEY_A]) {
            Player->Position.x -= velocity;
        }
        if(this->Keys[GLFW_KEY_D]) {
            Player->Position.x += velocity;
        }
        if(this->Keys[GLFW_KEY_SPACE] && !Player->IsShooting) {
            Player->Shoot();
            Player->IsShooting = true;

        }
        if(!this->Keys[GLFW_KEY_SPACE]){
            Player->IsShooting = false;
        }
    }

}
void game::ResetPlayer() {

    if(Player->Position.x >= this->Width * 2.0f || Player->Position.x <= 0.0f || Player->Position.y >= this->Height * 2.0f || Player->Position.y <= 0.0f || !Player->IsSolid) {
        Player->Reset(glm::vec2(this->Width / 2.0f, this->Height / 2.0f),glm::vec2(0.0f));
        this->Stages.clear();

        this->Stage = 0;
        this->Stages.push_back(stages[Stage]);

        this->Stages[this->Stage].Draw(*Renderer);
    }

}
void game::DoCollisions(float dt) {

    for(enemy_object& enemy : this->Stages[Stage].Enemies) {
        if(CheckCollisionsBetweenObjects(*Player, enemy)) {
            Player->LifeTime -= dt;
            Player->Color = glm::vec3(1.0f,0.0f, 0.0f);
            if(Player->LifeTime <= 0.0f) {
                Player->Health -= 20.0f;
                Player->LifeTime = LIFE_TIME;
            }
        }
    }
    for(game_object& brick : this->Stages[Stage].Bricks) {
        if(CheckCollisionsBetweenObjects(*Player, brick))
                Player->Health -= 100.0f;
    }
    for(auto projectile : Player->Projectiles) {
        for(enemy_object& enemy : this->Stages[Stage].Enemies) {
            if(CheckCollisionsBetweenObjects(*projectile, enemy)) {
                enemy.Health -= 50.0f;
                projectile->IsSolid  = false;
            }
        }
    }
    for(unsigned int i = 0; i < Stages[Stage].Enemies.size(); i++) {
        for(unsigned int j = i + 1; j < Stages[Stage].Enemies.size(); j++) {
            if(CheckCollisionsBetweenObjects(Stages[Stage].Enemies[i], Stages[Stage].Enemies[j])) {
                this->Stages[Stage].Enemies[i].Position += 2.0f;
            }
        }
        for(unsigned int i = 0; i < Stages[Stage].Bricks.size(); i++) {
            for(unsigned int j = i + 1; j < Stages[Stage].Bricks.size(); j++) {
                if(CheckCollisionsBetweenObjects(Stages[Stage].Bricks[i], Stages[Stage].Bricks[j])) {
                        this->Stages[Stage].Bricks[i].Position += 2.0f;
                }
            }
        }
    }
}
void game::ProcessMouse(double xPosIn, double yPosIn) {

    float xPos = static_cast<float>(xPosIn);
    float yPos = static_cast<float>(yPosIn);

    glm::vec2 playerCenter = Player->Position + Player->Size / 2.0f;
    glm::vec2 mouseWorldPos = ScreenToWorld(xPos, yPos);

    Player->Direction = mouseWorldPos - playerCenter;
    float angle = atan2(Player->Direction.x, -Player->Direction.y);
    Player->Rotation = glm::degrees(angle) * SENSITIVITY;
}

void game::ProcessCamera(float dt) {

    glm::vec2 playerCenter = Player->Position + Player->Size / 2.0f;
    glm::vec3 cameraPos = glm::vec3(playerCenter, 1.0f);
    this->ViewMatrix = glm::mat4(1.0f);
    ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraPos.x + Width / 2.0f, -cameraPos.y + Height / 2.0f, 0.0f)) * dt;
    resource_manager::GetShader("sprite").SetMatrix4x4("view",ViewMatrix);

}
glm::vec2 game::ScreenToWorld(float xPos, float yPos)
{
    float xNDC = (2.0f * xPos) / Width - 1.0f;
    float yNDC = 1.0f - (2.0f * yPos) / Height;
    glm::vec4 screenPos = glm::vec4(xNDC, yNDC, 0.0f, 1.0f);

    glm::vec2 playerCenter = Player->Position + Player->Size / 2.0f;
    glm::vec3 cameraPos = glm::vec3(playerCenter, 1.0f);
    this->ViewMatrix = glm::mat4(1.0f);
    this->ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraPos.x + Width / 2.0f, -cameraPos.y + Height / 2.0f, 0.0f));
    glm::mat4 viewProjection = this->ProjectionMatrix * this->ViewMatrix;
    glm::mat4 inverseVP = glm::inverse(viewProjection);
    glm::vec4 worldPos = inverseVP * screenPos;

    return glm::vec2(worldPos);
}
glm::vec2 game::WorldToScreen(glm::vec2 position, glm::mat4 view, glm::mat4 projection) {

    glm::vec4 clipSpacePos = projection * view * glm::vec4(position, 0.0f, 1.0f);

    glm::vec3 ndcSpacePos = glm::vec3(clipSpacePos) / clipSpacePos.w;

    glm::vec2 screenPos;
    screenPos.x = (ndcSpacePos.x + 1.0f) * 0.5f * this->Width;
    screenPos.y = (1.0f - ndcSpacePos.y) * 0.5f * this->Height;

    return screenPos;
 }
