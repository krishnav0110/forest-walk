#include "FBO.hpp"
#include <iostream>
#include "settings.h"

FBO::FBO(int width, int height, bool multisample, std::vector<std::string> &names) {
    unsigned int attachmentCount = names.size();
    this->width = width;
    this->height = height;

    float quadVertices[] = {
        -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f
    };
    float quadTex[] = {
        0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };
    model.vao.Bind();
    model.load(4, GL_TRIANGLE_STRIP);
    model.loadVBO(std::string("positions"), sizeof(quadVertices), 2, 2 * sizeof(float), &quadVertices, GL_STATIC_DRAW);
    model.loadVBO(std::string("textures"), sizeof(quadTex), 2, 2 * sizeof(float), &quadTex, GL_STATIC_DRAW);
    model.vao.Unbind();

	glGenFramebuffers(1, &ID);
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
    std::vector<GLuint> attachments;

    for(int i = 0; i < attachmentCount; ++i) {
        texIDs.insert({names[i], 0});
        glGenTextures(1, &(texIDs[names[i]]));
        if(multisample) {
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texIDs[names[i]]);
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 1, GL_RGBA, width, height, GL_TRUE);
        } else {
            glBindTexture(GL_TEXTURE_2D, texIDs[names[i]]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        if(multisample) {
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D_MULTISAMPLE, texIDs[names[i]], 0);
        } else {
            glBindTexture(GL_TEXTURE_2D, 0);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texIDs[names[i]], 0);
        }
        attachments.emplace_back(GL_COLOR_ATTACHMENT0 + i);
    }
    glDrawBuffers(attachmentCount, attachments.data());
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer not complete!\n";
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
    glViewport(0, 0, width, height);
}

void FBO::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void FBO::Delete() {
	glDeleteFramebuffers(1, &ID);
}