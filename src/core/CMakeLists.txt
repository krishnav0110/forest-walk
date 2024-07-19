add_library(krev-core
    VAO.cpp
    VBO.cpp
    FBO.cpp
    Model.cpp
    Renderer.cpp
)

set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/lib/SFML-2.6.1")
set(CMAKE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/lib/SFML-2.6.1/lib/")
find_package(SFML COMPONENTS system window graphics REQUIRED)

target_link_libraries(krev-core
    sfml-graphics
)

target_include_directories(krev-core PUBLIC "${PROJECT_SOURCE_DIR}/lib/glm")

target_include_directories(krev-core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)