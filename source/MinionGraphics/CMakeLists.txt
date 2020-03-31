cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(DEMO TRUE)

set(MINION_GRAPHICS MinionGraphics)
project(MinionGraphics)

set(SOURCE  Graphics_impl.cpp
            MinionGraphics_DevInterface.cpp
            MinionGraphicsException.cpp
            rendering/Camera.cpp
            rendering/RenderTexture.cpp
            rendering/ShaderProgram.cpp
            rendering/Texture.cpp
            rendering/renderers/DeferredRenderer.cpp
            rendering/renderers/ShadowMapRenderer.cpp
            models/Cube.cpp
            models/Mesh.cpp
            models/MeshLoader.cpp
            models/Model.cpp
            models/Plane.cpp
            models/Sphere.cpp
            models/Triangle.cpp
)

include_directories(./../../../Utilities/source/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../external/glm/
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../external/bullet3/src
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../external/glfw/include)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
add_library(${MINION_GRAPHICS} SHARED ${SOURCE})

# Open GL libs
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(${MINION_GRAPHICS} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(${MINION_GRAPHICS} ${GLEW_LIBRARIES})
endif()

find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(${MINION_GRAPHICS} ${GLFW_LIBRARIES})
#######################

set_target_properties(${MINION_GRAPHICS} PROPERTIES PREFIX "")
set_target_properties(${MINION_GRAPHICS} PROPERTIES OUTPUT_NAME "miniongraphics")

IF(${DEMO})
    MESSAGE(DEMO)
    add_executable(${MINION_GRAPHICS}_demo MinionGraphicsDemo.cpp)
    target_link_libraries(${MINION_GRAPHICS}_demo ${MINION_GRAPHICS})
ENDIF()