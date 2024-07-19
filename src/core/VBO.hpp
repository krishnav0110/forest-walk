#ifndef _VBO_H_
#define _VBO_H_

#include <GL/glew.h>

class VBO {
public:
	GLuint ID;
	VBO();

	void Load(GLsizeiptr size, const void *data, GLenum usage);
	void Update(GLintptr offset, GLsizeiptr size, const void *data);
	void Update(GLsizeiptr size, const void *data);

	void Bind() const;
	void Unbind() const;
	void Delete();
};

#endif