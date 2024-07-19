#include <iostream>
#include "FBO.hpp"
#include "Renderer.hpp"

FBO::FBO(const glm::ivec2 &size, bool multisample, const std::vector<std::string> &names) {
    this->size = size;
    int attachmentCount = (int)names.size();

    float quadVertices[] = {
        -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f
    };
    float quadTex[] = {
        0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };
    model.vao.Bind();
    model.Update(4, GL_TRIANGLE_STRIP);
    model.LoadVBO(std::string("positions"), sizeof(quadVertices), 2, 2 * sizeof(float), &quadVertices, GL_STATIC_DRAW);
    model.LoadVBO(std::string("textures"), sizeof(quadTex), 2, 2 * sizeof(float), &quadTex, GL_STATIC_DRAW);
    model.vao.Unbind();

	glGenFramebuffers(1, &ID);
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
    std::vector<GLuint> attachments;

    for(int i = 0; i < attachmentCount; ++i) {
        texIDs.insert({names[i], 0});
        glGenTextures(1, &(texIDs[names[i]]));
        if(multisample) {
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texIDs[names[i]]);
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 1, GL_RGBA, size.x, size.y, GL_TRUE);
        } else {
            glBindTexture(GL_TEXTURE_2D, texIDs[names[i]]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_FLOAT, NULL);
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
        std::cerr << "Framebuffer not complete!\n";
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::Bind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
    glViewport(0, 0, size.x, size.y);
}

void FBO::Unbind() const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::Delete() {
	glDeleteFramebuffers(1, &ID);
}