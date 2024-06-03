#include <iostream>
#include <thread>
#include <chrono>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <glm/ext.hpp>
#include "settings.h"
#include "Renderer.hpp"
#include "Camera.hpp"
#include "Sky.hpp"
#include "Forest.hpp"
#include "LensFlare.hpp"
#include "FBO.hpp"

int main(int argv, char** args) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    settings.minorVersion = 3;
    sf::Window window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ForestWalk", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    window.setActive(true);

    if(GLEW_OK != glewInit()) {
        std::cout << "GLEW initialization failed";
        exit(1);
    }

    // glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    sf::Shader skyShader;
    sf::Shader sunShader;
    sf::Shader forestShader;
    sf::Shader leavesShader;
    sf::Shader godRaysShader;
    sf::Shader blurShader;
    sf::Shader finalShader;
    sf::Shader flareShader;
    sf::Shader sampleShader;
    skyShader.loadFromFile("shaders/sky.vert", "shaders/sky.frag");
    sunShader.loadFromFile("shaders/sun.vert", "shaders/sun.frag");
    forestShader.loadFromFile("shaders/forest.vert", "shaders/forest.geom", "shaders/forest.frag");
    leavesShader.loadFromFile("shaders/leaves.vert", "shaders/leaves.geom", "shaders/leaves.frag");
    godRaysShader.loadFromFile("shaders/godrays.vert", "shaders/godrays.frag");
    blurShader.loadFromFile("shaders/blur.vert", "shaders/blur.frag");
    finalShader.loadFromFile("shaders/final.vert", "shaders/final.frag");
    flareShader.loadFromFile("shaders/flare.vert", "shaders/flare.frag");
    sampleShader.loadFromFile("shaders/sample.vert", "shaders/sample.frag");

    Camera camera(glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 1.0f);

    forestShader.setUniform("viewMat", sf::Glsl::Mat4(glm::value_ptr(camera.viewMatrix())));
    forestShader.setUniform("projectionMat", sf::Glsl::Mat4(glm::value_ptr(camera.projectionMatrix())));
    leavesShader.setUniform("viewMat", sf::Glsl::Mat4(glm::value_ptr(camera.viewMatrix())));
    leavesShader.setUniform("projectionMat", sf::Glsl::Mat4(glm::value_ptr(camera.projectionMatrix())));
    // glUniform1i(glGetUniformLocation(forestShader.ID, "texture1"), 0);
    // godRaysShader.setUniform("scene", 0);
    // godRaysShader.setUniform("bloomBlur", 1);

    Renderer renderer;
    Sky sky;
    Forest forest;
    LensFlare lensFlare;

    FBO multiSampleFBO(WINDOW_WIDTH, WINDOW_HEIGHT, true, std::vector({std::string("normal"), std::string("bright")}));
    FBO hdrFBO(WINDOW_WIDTH, WINDOW_HEIGHT, false, std::vector({std::string("normal"), std::string("bright")}));
    FBO godRaysFBO(WINDOW_WIDTH * 0.75f, WINDOW_HEIGHT * 0.75f, false, std::vector({std::string("godrays")}));
    FBO blurFBO(WINDOW_WIDTH * 1.0f, WINDOW_HEIGHT * 1.0f, false, std::vector({std::string("blur")}));

    godRaysShader.setUniform("sunPos", sky.sunPos);
    
    bool running = true;
    float dt = 1.0f / 60.0f;
    float delta = 0.0f;
    sf::Clock now;

    while(running) {
        sf::Time elapsedTime = now.restart();
        delta += elapsedTime.asSeconds();

        if(delta < dt) {
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            continue;
        }
        delta = 0.0f;
        
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    running = false;
                break;
                case sf::Event::Resized:
                    glViewport(0, 0, event.size.width, event.size.height);
                break;
                case sf::Event::MouseButtonPressed:
                    forest.windForce += 20.0f;
                break;
                case sf::Event::MouseButtonReleased:
                    forest.windForce -= 20.0f;
                break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::W) {
                        camera.pos.z -= 0.5f * dt;
                    } else if(event.key.code == sf::Keyboard::S) {
                        camera.pos.z += 0.5f * dt;
                    }
                break;
            }
        }

        camera.pos.z -= 0.1f * dt;
        camera.update();
        forest.generate(camera);
        forest.update(dt, camera);
        lensFlare.update(sky.sunPos);

        // rendering to multisample fbo
        multiSampleFBO.Bind();

        forestShader.setUniform("viewMat", sf::Glsl::Mat4(glm::value_ptr(camera.viewMatrix())));
        renderer.render(sky.model, &skyShader);
        renderer.render(sky.sunModel, sky.sunTex, &sunShader);
        renderer.render(forest.branchesModel, &forestShader);

        leavesShader.setUniform("viewMat", sf::Glsl::Mat4(glm::value_ptr(camera.viewMatrix())));
        renderer.render(forest.leavesModel, forest.leafTex, &leavesShader);

        flareShader.setUniform("alpha", lensFlare.alpha);
        renderer.render(lensFlare.model, lensFlare.flareTex, &flareShader);
        multiSampleFBO.Unbind();

        // rendering to the hdr fbo
        glBindFramebuffer(GL_READ_FRAMEBUFFER, multiSampleFBO.ID);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, hdrFBO.ID);
        for(int i = 0; i < 2; ++i) {
            glReadBuffer(GL_COLOR_ATTACHMENT0 + i);
            glDrawBuffer(GL_COLOR_ATTACHMENT0 + i);
            glClear(GL_COLOR_BUFFER_BIT);
            glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        }
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        // rendering to the god rays fbo
        godRaysFBO.Bind();
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.render(hdrFBO.model, hdrFBO.texIDs["bright"], &godRaysShader);
        godRaysFBO.Unbind();

        // rendering to blur fbo
        blurFBO.Bind();
        renderer.render(blurFBO.model, godRaysFBO.texIDs["godrays"], &blurShader);
        blurFBO.Unbind();

        // rendering to the screen
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.render(godRaysFBO.model, std::vector({hdrFBO.texIDs["normal"], blurFBO.texIDs["blur"]}), &finalShader);

        window.display();
    }

    multiSampleFBO.Delete();
    hdrFBO.Delete();
    godRaysFBO.Delete();
    blurFBO.Delete();
    return 0;
}