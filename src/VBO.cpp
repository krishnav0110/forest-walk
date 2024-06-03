#include "VBO.hpp"

VBO::VBO() {
	glGenBuffers(1, &ID);
}

void VBO::load(GLsizeiptr size, const void *data, GLenum usage) {
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	Unbind();
}

void VBO::update(GLsizeiptr size, const void *data) {
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	Unbind();
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}