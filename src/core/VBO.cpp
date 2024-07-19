#include "VBO.hpp"

VBO::VBO() {
	glGenBuffers(1, &ID);
}

void VBO::Load(GLsizeiptr size, const void *data, GLenum usage) {
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	Unbind();
}

void VBO::Update(GLintptr offset, GLsizeiptr size, const void *data) {
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	Unbind();
}

void VBO::Update(GLsizeiptr size, const void *data) {
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	Unbind();
}

void VBO::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}