#ifndef _VAO_H_
#define _VAO_H_

#include <GL/glew.h>
#include "VBO.hpp"

class VAO {
public:
	GLuint ID;
	VAO();

	void LinkAttrib(const VBO &vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, const void* offset);
	void Bind() const;
	void Unbind() const;
	void Delete();
};

#endif