#ifndef _VBO_H_
#define _VBO_H_

#include <GL/glew.h>

class VBO {
public:
	GLuint ID;
	VBO();

	void load(GLsizeiptr size, const void *data, GLenum usage);
	void update(GLsizeiptr size, const void *data);

	void Bind();
	void Unbind();
	void Delete();
};

#endif