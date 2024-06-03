#ifndef _VAO_H_
#define _VAO_H_

#include <GL/glew.h>
#include "VBO.hpp"

class VAO {
public:
	GLuint ID;
	VAO();

	void LinkAttrib(VBO &vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif