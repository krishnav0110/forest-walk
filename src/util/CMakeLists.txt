add_library(krev-util
    MathUtil.cpp
)

target_include_directories(krev-util PUBLIC "${PROJECT_SOURCE_DIR}/lib/glm")

target_include_directories(krev-util PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)