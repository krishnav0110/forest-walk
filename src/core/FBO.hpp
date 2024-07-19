#ifndef _FBO_H_
#define _FBO_H_

#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Model.hpp"

class FBO {
private:
	glm::ivec2 size;

public:
	GLuint ID;
	std::map<std::string, GLuint> texIDs;
    Model model;
	FBO(const glm::ivec2 &size, bool multisample, const std::vector<std::string> &names);

	void Bind() const;
	void Unbind() const;
	void Delete();
};

#endif