#include <iostream>
#include <thread>
#include <chrono>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <glm/ext.hpp>
#include "core/Renderer.hpp"
#include "core/FBO.hpp"
#include "Camera.hpp"
#include "Sky.hpp"
#include "Forest.hpp"
#include "LensFlare.hpp"





int main(int argv, char** args) {
    glm::ivec2 windowSize(768, 512);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
    settings.minorVersion = 3;
    sf::Window window(sf::VideoMode(windowSize.x, windowSize.y), "ForestWalk", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    window.setActive(true);

    if(GLEW_OK != glewInit()) {
        std::cout << "GLEW initialization failed";
        exit(1);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera camera(glm::radians(45.0f), (float)windowSize.x / windowSize.y, 0.1f, 10.0f);

    Sky sky(windowSize);
    Forest forest;
    LensFlare lensFlare(windowSize);

    FBO multiSampleFBO(windowSize, true, std::vector({std::string("normal"), std::string("bright")}));
    FBO hdrFBO(windowSize, false, std::vector({std::string("normal"), std::string("bright")}));
    FBO godRaysFBO({windowSize.x * 0.75f, windowSize.y * 0.75f}, false, std::vector({std::string("godrays")}));
    FBO blurFBO(windowSize, false, std::vector({std::string("blur")}));



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

    forestShader.setUniform("viewMat", sf::Glsl::Mat4(glm::value_ptr(camera.ViewMatrix())));
    forestShader.setUniform("projectionMat", sf::Glsl::Mat4(glm::value_ptr(camera.ProjectionMatrix())));

    leavesShader.setUniform("viewMat", sf::Glsl::Mat4(glm::value_ptr(camera.ViewMatrix())));
    leavesShader.setUniform("projectionMat", sf::Glsl::Mat4(glm::value_ptr(camera.ProjectionMatrix())));

    godRaysShader.setUniform("sunPos", sf::Glsl::Vec2(sky.sunPos.x, sky.sunPos.y));
    


    bool running = true;
    float dt = 1.0f / 60.0f;
    float delta = 0.0f;
    sf::Clock now;

    while(running) {
        sf::Time elapsedTime = now.restart();
        delta += elapsedTime.asSeconds();

        if(delta < dt) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
            }
        }

        camera.pos.z -= 0.1f * dt;
        camera.Update();
        forest.Generate(camera);
        forest.Update(dt, camera);
        lensFlare.Update(sky.sunPos);

        // rendering to multisample fbo
        multiSampleFBO.Bind();

        forestShader.setUniform("viewMat", sf::Glsl::Mat4(glm::value_ptr(camera.ViewMatrix())));
        Renderer::render(sky.model, &skyShader);
        Renderer::render(sky.sunModel, sky.sunTex, &sunShader);
        Renderer::render(forest.branchesModel, &forestShader);

        leavesShader.setUniform("viewMat", sf::Glsl::Mat4(glm::value_ptr(camera.ViewMatrix())));
        Renderer::render(forest.leavesModel, forest.leafTex, &leavesShader);

        // rendering to the hdr fbo
        Renderer::render(multiSampleFBO, hdrFBO, 2);

        // rendering to the god rays fbo
        godRaysFBO.Bind();
        glClear(GL_COLOR_BUFFER_BIT);
        Renderer::render(hdrFBO.model, hdrFBO.texIDs["bright"], &godRaysShader);

        // rendering to blur fbo
        blurFBO.Bind();
        Renderer::render(blurFBO.model, godRaysFBO.texIDs["godrays"], &blurShader);
        blurFBO.Unbind();

        // rendering to the screen
        glClear(GL_COLOR_BUFFER_BIT);
        Renderer::render(godRaysFBO.model, std::vector({hdrFBO.texIDs["normal"], blurFBO.texIDs["blur"]}), &finalShader);

        flareShader.setUniform("alpha", lensFlare.alpha);
        Renderer::render(lensFlare.model, lensFlare.flareTex, &flareShader);
        multiSampleFBO.Unbind();

        window.display();
    }

    multiSampleFBO.Delete();
    hdrFBO.Delete();
    godRaysFBO.Delete();
    blurFBO.Delete();
    return 0;
}