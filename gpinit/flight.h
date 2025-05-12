//
// Created by student on 4/21/21.
//
#ifndef GPINIT_FLIGHT_H
#define GPINIT_FLIGHT_H
#include <GLFW/glfw3.h>
#include "gpinit/camera.h"
#include "gpinit/shader.h"
// Method Headers
void framebufferSizeCallback(GLFWwindow * window, int width, int height);
void cursorPosCallback(GLFWwindow * window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInputs(GLFWwindow * window);
void set_normals();
void scrollCallback(GLFWwindow * window, double xoffset, double yoffset);
#endif //FLIGHT_CONE_H