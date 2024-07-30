#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "Model.hpp"
#include "FBO.hpp"

class Renderer {
private:
    static void render(const Model &model);

public:
    static void render(const Model &model, const sf::Shader *shader);
    static void render(const Model &model, const sf::Texture &tex, const sf::Shader *shader);
    static void render(const Model &model, GLuint texID, const sf::Shader *shader);
    static void render(const Model &model, const std::vector<GLuint> &texIDs, const sf::Shader *shader);
    static void render(const FBO &srcFBO, const FBO &destFBO, unsigned int attachmentCount);
};

#endif