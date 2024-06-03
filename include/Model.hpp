#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>
#include <vector>
#include <map>
#include "VAO.hpp"

class Model {
public:
    VAO vao;
    GLuint vaoLayout;
    std::map<std::string, VBO> vbos;
    unsigned int vertexCount;
    GLenum mode;

    Model();
    void load(unsigned int vertexCount, GLenum mode);
    void loadVBO(std::string &vboName, GLsizeiptr size, GLuint numComponents, GLsizeiptr stride, void *data, GLenum usage);
    void updateVBO(std::string &vboName, GLsizeiptr size, void *data);
    ~Model();
};

#endif