#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>
#include <vector>
#include <map>
#include "VAO.hpp"

class Model {
private:
    GLuint vaoLayout;
    unsigned int vertexCount;
    GLenum mode;

public:
    VAO vao;
    std::map<std::string, VBO> vbos;

    Model();
    void Update(unsigned int vertexCount);
    void Update(unsigned int vertexCount, GLenum mode);

    void LoadVBO(const std::string &vboName, GLsizeiptr size, GLuint numComponents, GLsizei stride, const void *data, GLenum usage);
    void UpdateVBO(const std::string &vboName, GLsizeiptr size, const void *data);
    void UpdateVBO(const std::string &vboName, GLintptr offset, GLsizeiptr size, const void *data);

    unsigned int GetVertexCount() const;
    GLenum GetMode() const;

    void Delete();
};

#endif