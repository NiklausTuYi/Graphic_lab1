cmake_minimum_required(VERSION 3.8)
project(CG1)
set(CMAKE_CXX_STANDARD 11)
include_directories (/System/Library/Frameworks)
find_library (GLUT_LIBRARY GLUT)
find_library (OpenGL_LIBRARY OpenGL)
find_library (APPKIT_LIBRARY APPKIT)
mark_as_advanced (GLUT_LIBRARY OpenGL_LIBRARY APPKIT_LIBRARY)

# 添加頭文檔
set(GLEW_H /usr/local/Cellar/glew/2.1.0/include/GL)
set(GLFW_H /usr/local/Cellar/glfw/3.2.1/include/GLFW)
set(GL_H /usr/local/include)
include_directories(${GLEW_H} ${GLFW_H} ${GL_H})

# 添加目標鏈接
set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.dylib)
link_libraries(${GLUT_LIBRARY} ${OpenGL_LIBRARY} ${APPKIT_LIBRARY} ${GLEW_LINK} ${GLFW_LINK})

# 執行編譯命令
set(SOURCE_FILES main.cpp model.h math.h texture.h drawWall.h)
add_executable(CG1 ${SOURCE_FILES})
