//
// Created by student on 4/21/21.
//
#ifndef FLIGHT_FLIGHT_H
#define FLIGHT_FLIGHT_H
#include <GLFW/glfw3.h>
#include "other/camera.h"
#include "other/shader.h"
// Method Headers
void framebufferSizeCallback(GLFWwindow * window, int width, int height);
void cursorPosCallback(GLFWwindow * window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInputs(GLFWwindow * window);
void perFrameTimeLogic();
void get_center();
void set_normals();
std::tuple<GLuint, GLuint> bind_VAO_VBO();
GLFWwindow * init_glfw();
void scrollCallback(GLFWwindow * window, double xoffset, double yoffset);
void pass_params_to_shader(Shader shader, Camera camera);
#endif //FLIGHT_CONE_H