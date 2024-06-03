#ifndef _FBO_H_
#define _FBO_H_

#include <map>
#include <GL/glew.h>
#include "Model.hpp"

class FBO {
private:
	int width;
	int height;

public:
	GLuint ID;
	std::map<std::string, GLuint> texIDs;
    Model model;
	FBO(int width, int height, bool multisample, std::vector<std::string> &names);

	void Bind();
	void Unbind();
	void Delete();
};

#endif