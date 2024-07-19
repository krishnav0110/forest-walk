#include "Model.hpp"
#include <GL/glew.h>

Model::Model() {
    this->vertexCount = 0;
    this->mode = GL_POINTS;
    this->vaoLayout = 0;
}

void Model::Update(unsigned int vertexCount) {
    this->vertexCount = vertexCount;
}
void Model::Update(unsigned int vertexCount, GLenum mode) {
    this->vertexCount = vertexCount;
    this->mode = mode;
}





void Model::LoadVBO(const std::string &vboName, GLsizeiptr size, GLuint numComponents, GLsizei stride, const void *data, GLenum usage) {
    vbos.insert({vboName, VBO()});
    VBO &vbo = vbos[vboName];

    vbo.Load(size, data, usage);

    vao.LinkAttrib(vbo, vaoLayout, numComponents, GL_FLOAT, stride, (void*)0);
    vaoLayout++;
}

void Model::UpdateVBO(const std::string &vboName, GLsizeiptr size, const void *data) {
    VBO &vbo = vbos[vboName];
    vbo.Update(size, data);
}
void Model::UpdateVBO(const std::string &vboName, GLintptr offset, GLsizeiptr size, const void *data) {
    VBO &vbo = vbos[vboName];
    vbo.Update(offset, size, data);
}





unsigned int Model::GetVertexCount() const {
    return vertexCount;
}
GLenum Model::GetMode() const {
    return mode;
}





void Model::Delete() {
    vao.Delete();
    for(auto& [vboName, vbo]: vbos) {
        vbo.Delete();
    }
    vbos.clear();
}