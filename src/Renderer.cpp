#include <iostream>
#include <GL/glew.h>
#include "Renderer.hpp"

void Renderer::render(Model &model, sf::Shader *shader) {
    sf::Shader::bind(shader);
    model.vao.Bind();
    glDrawArrays(model.mode, 0, model.vertexCount);
    model.vao.Unbind();
}

void Renderer::render(Model &model, sf::Texture &tex, sf::Shader *shader) {
    sf::Shader::bind(shader);
    sf::Texture::bind(&tex);
    model.vao.Bind();
    glDrawArrays(model.mode, 0, model.vertexCount);
    model.vao.Unbind();
}

void Renderer::render(Model &model, GLuint texID, sf::Shader *shader) {
    sf::Shader::bind(shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texID);
    model.vao.Bind();
    glDrawArrays(model.mode, 0, model.vertexCount);
    model.vao.Unbind();
}

void Renderer::render(Model &model, std::vector<GLuint> &texIDs, sf::Shader *shader) {
    sf::Shader::bind(shader);
    for(int i = 0; i < texIDs.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texIDs[i]);
    }
    model.vao.Bind();
    glDrawArrays(model.mode, 0, model.vertexCount);
    model.vao.Unbind();
}