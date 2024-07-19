#include <iostream>
#include <GL/glew.h>
#include "Renderer.hpp"

void Renderer::render(const Model &model) {
    model.vao.Bind();
    glDrawArrays(model.GetMode(), 0, model.GetVertexCount());
    model.vao.Unbind();
}

void Renderer::render(const Model &model, const sf::Shader *shader) {
    sf::Shader::bind(shader);
    render(model);
}

void Renderer::render(const Model &model, const sf::Texture &tex, const sf::Shader *shader) {
    sf::Shader::bind(shader);
    sf::Texture::bind(&tex);
    render(model);
}

void Renderer::render(const Model &model, GLuint texID, const sf::Shader *shader) {
    sf::Shader::bind(shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texID);
    render(model);
}

void Renderer::render(const Model &model, const std::vector<GLuint> &texIDs, const sf::Shader *shader) {
    sf::Shader::bind(shader);
    for(int i = 0; i < texIDs.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texIDs[i]);
    }
    render(model);
}