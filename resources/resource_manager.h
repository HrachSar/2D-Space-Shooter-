#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include "../texture/texture.h"
#include "../shader/shader.h"

class resource_manager {
public:
    static std::map<std::string, texture> Texture;
    static std::map<std::string, shader> Shader;

    static shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    static texture LoadTexture(const char* file, bool alpha, std::string name);

    static shader GetShader(std::string name);
    static texture GetTexture(std::string name);

    static void Clear();
private:
    resource_manager();
    static shader LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    static texture LoadTextureFromFile(const char* file, bool alpha);
};

#endif //RESOURCE_MANAGER_H
