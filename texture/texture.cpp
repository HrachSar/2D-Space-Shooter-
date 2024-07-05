#include "texture.h"

#include <iostream>
#include <GL/gl.h>
#include <GL/gl.h>
#include <GL/gl.h>
#include <GL/gl.h>
#include <GL/gl.h>

texture::texture() : Width(0), Height(0), Internal_Format(GL_RGB),
                     Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR) {
    glGenTextures(1, &this->ID);
}

void texture::Generate(unsigned int width, unsigned int height, unsigned char *data) {
    this->Width = width;
    this->Height = height;

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);

    glBindTexture(GL_TEXTURE_2D, 0);
}
void texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}


