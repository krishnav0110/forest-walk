#include "VAO.hpp"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, const void* offset) {
	vbo.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

void VAO::Bind() const {
	glBindVertexArray(ID);
}

void VAO::Unbind() const {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}