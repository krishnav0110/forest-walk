#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <SFML/Graphics.hpp>
#include "Model.hpp"

class Renderer {
private:

public:
    void render(Model &model, sf::Shader *shader);
    void render(Model &model, sf::Texture &tex, sf::Shader *shader);
    void render(Model &model, GLuint texID, sf::Shader *shader);
    void render(Model &model, std::vector<GLuint> &texIDs, sf::Shader *shader);
};

#endif