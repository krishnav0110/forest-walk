#include "Model.hpp"
#include <GL/glew.h>

Model::Model() {
    this->vertexCount = 0;
    this->mode = GL_POINTS;
    this->vaoLayout = 0;
}

void Model::load(unsigned int vertexCount, GLenum mode) {
    this->vertexCount = vertexCount;
    this->mode = mode;
}

void Model::loadVBO(std::string &vboName, GLsizeiptr size, GLuint numComponents, GLsizeiptr stride, void *data, GLenum usage) {
    vbos.insert({vboName, VBO()});
    VBO &vbo = vbos[vboName];

    vbo.load(size, data, usage);

    vao.LinkAttrib(vbo, vaoLayout, numComponents, GL_FLOAT, stride, (void*)0);
    vaoLayout++;
}

void Model::updateVBO(std::string &vboName, GLsizeiptr size, void *data) {
    VBO &vbo = vbos[vboName];
    vbo.update(size, data);
}

// void Model::loadVertices(std::vector<Vertex> &vertices, GLenum mode) {
//     this->vertexCount = vertices.size();
//     this->mode = mode;
//     vao.Bind();

//     vbo.load(vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

//     // position
//     vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
//     // color
//     vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    
//     vao.Unbind();
// }

// void Model::updateVertices(std::vector<Vertex> &vertices) {
//     this->vertexCount = vertices.size();
//     vbo.update(vertices.size() * sizeof(Vertex), vertices.data());
// }

Model::~Model() {
    vao.Delete();
    for(auto& [vboName, vbo]: vbos) {
        vbo.Delete();
    }
    vbos.clear();
}