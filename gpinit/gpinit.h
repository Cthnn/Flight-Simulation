#ifndef GPINIT_H
#define GPINIT_H

#include <bits/stdc++.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "gpinit/shader.h"

GLFWwindow * init_glfw(unsigned int screenWidth, unsigned int screenHeight,
                        GLFWcursorposfun cursorPosCallback, GLFWkeyfun key_callback,
                        GLFWframebuffersizefun framebufferSizeCallback,
                        GLFWmousebuttonfun mouseButtonCallback, GLFWscrollfun scrollCallback){
    //Initialize Window
    //Shape Display Modes
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow * window = glfwCreateWindow(screenWidth, screenHeight, "Sim", nullptr, nullptr);
    if (!window)
    {
        std::cout << std::unitbuf
                  << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                  << "\n[ERROR] " << "Failed to create GLFW window!"
                  << std::nounitbuf << std::endl;
        glfwTerminate();
        std::abort();
    }

    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetScrollCallback(window, scrollCallback);


    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << std::unitbuf
                  << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                  << "\n[ERROR] " << "Failed to initialize GLAD!"
                  << std::nounitbuf << std::endl;

        std::abort();
    }

    return window;
}

void terminate_window(GLuint VAO, GLuint vertexVBO, GLuint normalVBO, Shader shader){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &normalVBO);
    glDeleteProgram(shader.getShaderProgramHandle());
    glfwTerminate();
}

std::tuple<GLuint, GLuint, GLuint> bind_VAO_VBO(unsigned int screenWidth, unsigned int screenHeight,
                                        std::vector<glm::vec3> vertices, std::vector<glm::vec3> normalV){
    // Bind VAO and VBOS
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint vertexVBO;
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void *>(0));

    GLuint normalVBO;
    glGenBuffers(1, &normalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glBufferData(GL_ARRAY_BUFFER, normalV.size() * sizeof(glm::vec3), normalV.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void *>(0));

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, screenWidth, screenHeight);
    return std::make_tuple(VAO, vertexVBO, normalVBO);
}

std::tuple<float, float> perFrameTimeLogic(float lastFrame)
{
    auto currentFrame = static_cast<float>(glfwGetTime());
    return std::make_tuple(currentFrame - lastFrame,currentFrame);

}

#endif 