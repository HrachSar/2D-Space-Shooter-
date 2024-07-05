#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "../core/stb_image.h"

std::map<std::string, texture> resource_manager::Texture;
std::map<std::string, shader> resource_manager::Shader;

shader resource_manager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name) {
    Shader[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shader[name];
}
shader resource_manager::GetShader(std::string name) {
    return Shader[name];
}
texture resource_manager::GetTexture(std::string name) {
    return Texture[name];
}

texture resource_manager::LoadTexture(const char *file, bool alpha, std::string name) {
    Texture[name] = LoadTextureFromFile(file, alpha);
    return Texture[name];
}
void resource_manager::Clear() {
    for(auto iter : Shader) {
        glDeleteProgram(iter.second.ID);
    }
    for(auto iter : Texture) {
        glDeleteTextures(1, &iter.second.ID);
    }
}
shader resource_manager::LoadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile) {
    std::string vertexCode, fragmentCode, geometryCode;
    try {
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        if(gShaderFile != nullptr) {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }

    }catch (std::exception e) {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();

    shader _shader;
    _shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return _shader;
}

texture resource_manager::LoadTextureFromFile(const char *file, bool alpha) {
    texture _texture;

    if(alpha) {
        _texture.Image_Format = GL_RGBA;
        _texture.Internal_Format = GL_RGBA;
    }
    int width, height, nrChannels;

    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    _texture.Generate(width, height, data);
    stbi_image_free(data);

    return _texture;
}


