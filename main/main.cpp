#include <bits/stdc++.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "gpinit/gpinit.h"
#include "gpinit/world.h"
#include "gpinit/camera.h"
#include "gpinit/shader.h"
#include "gpinit/cube.h"
#include "gpinit/tetra.h"
#include "gpinit/oct.h"
#include "gpinit/cylinder.h"
#include "gpinit/cone.h"
#include "gpinit/torus.h"
#include "gpinit/ellipsoid.h"
#include "gpinit/dodecahedron.h"
#include "gpinit/icosahedron.h"
#include "gpinit/flight.h"


// Set Window Height and width
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 1024;
const unsigned int RAD = 17.7;

int curr = 0;
//header
void pass_params_to_shader(Shader shader, Camera camera);
enum class Modes {SMOOTH,FLAT,WIREFRAME};
Modes mode = Modes::SMOOTH;

// Mouse Variables
bool mousePressed = false;
bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

// Time Variables
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Position of light, Color of Light, and Object Color
const glm::vec3 lightPos(0.0f, 0.0f, 5.0f);
const glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
const glm::vec3 objColor(0.0f, 0.0f, 1.0f);

//Defining the shapes in the universe and their positions.
std::vector<Shape*> shapes = {new Cone,new Cube(),new Cylinder(),new Ellipsoid(),new Icosahedron(0),new Icosahedron(2),new Oct(),new Tetra(),new Torus(), new Dodecahedron()};
std::vector<glm::vec3> shapePos = {glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(2.0f, 5.0f, -15.0f),glm::vec3(-1.5f, -5.2f, -2.5f),glm::vec3(-3.8f, -2.0f, -12.3f),glm::vec3(2.4f, -0.4f, -10.5f),glm::vec3(-0.7f, 3.0f, -7.5f),glm::vec3(1.3f, -3.0f, -9.0f),glm::vec3(2.8f, 2.0f, -2.5f),glm::vec3(1.7f, 0.3f, -20.0f),glm::vec3(4.5f, -7.0f, -12.0f)};

std::vector<std::vector<GLuint>>indices;
std::vector<glm::vec3> vertices;
std::vector<glm::vec3> normalV;
std::vector<float>rot;

// Variables for Flight Simulation
bool flight = false;
bool vertical = true;
//Init camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
glm::vec3 center;
GLuint normalVBO;

int main()
{
    GLFWwindow * window = init_glfw(
        SCR_WIDTH, SCR_HEIGHT, cursorPosCallback, 
        key_callback, framebufferSizeCallback, mouseButtonCallback, 
        scrollCallback
    );
    // For Random Rotations, Initialize random seed
    srand(time(0));

    // Get Center of the world for camera
    center = get_center(shapePos);

    // Set normals of shapes for light
    set_normals();

    //Define shaders
    Shader shader("./shaders/phong.vert.glsl", "./shaders/phong.frag.glsl");
    GLuint VAO, vertexVBO;

    // Bind our VAO and VBOs
    std::tie(VAO,vertexVBO,normalVBO) = bind_VAO_VBO(SCR_WIDTH, SCR_HEIGHT, vertices, normalV);

    //Render Loop
    while (!glfwWindowShouldClose(window))
    {
        //For flight simulation. Circles around the universe based on "curr" which represents the start time of the flight simulation
        if(flight){
            if(vertical){
                glm::vec3 camPos(center.x,center.y+RAD*sin(M_PI*(1000-curr)/1000),center.z-RAD*cos(M_PI*(1000-curr)/1000));
                camera.changePos(camPos);
                curr+=1;
            }else{
                glm::vec3 camPos(center.x+RAD*sin(M_PI*(1000-curr)/1000),center.y,center.z-RAD*cos(M_PI*(1000-curr)/1000));
                camera.changePos(camPos);
                curr+=1;
            }

        }

        std::tie(deltaTime,lastFrame) = perFrameTimeLogic(lastFrame);
        processInputs(window);

        glClearColor(0.65f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // Pass parameters into our shaders
        pass_params_to_shader(shader, camera,
            SCR_WIDTH, SCR_HEIGHT, lightPos, 
            lightColor, objColor, shapes, shapePos, 
            indices, rot
        );
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    terminate_window(VAO, vertexVBO, normalVBO, shader);

    return 0;
}

void set_normals(){
    // Adds Vertices to a combined array and Normals to a combined normal arrays
    // Also save the starting indices and the how many vertices correspond with a shape
    GLuint prev = 0;
    for(int i = 0;i < shapes.size();i++){
        std::vector<glm::vec3>temp = shapes[i]->getVertices();
        std::vector<glm::vec3>normalTemp = shapes[i]->getNormal();
        std::vector<GLuint> pair = {prev,shapes[i]->getNumVertices()};
        prev += shapes[i]->getNumVertices();
        indices.push_back(pair);
        vertices.insert(vertices.end(),temp.begin(),temp.end());
        rot.push_back(rand()%91);
        if(mode == Modes::SMOOTH){
            normalV.insert(normalV.end(),temp.begin(),temp.end());
        }
        if(mode == Modes::FLAT){
            normalV.insert(normalV.end(),normalTemp.begin(),normalTemp.end());
        }
        if(mode == Modes::WIREFRAME){
            for(int i = 0;i < normalTemp.size();i++){
                glm::vec3 norm(0,0,0);
                normalV.push_back(norm);
            }
        }
    }
}

void framebufferSizeCallback(GLFWwindow * window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        curr = 0;
        camera.valueDefaults();
        if(flight){
            camera.changePos(glm::vec3(0.0f, 0.0f, 5.0f));
        }
        flight = !flight;

    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        curr = 0;
        camera.valueDefaults();
        vertical = true;

    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        curr = 0;
        camera.valueDefaults();
        vertical = false;
    }
    if(glfwGetKey(window,GLFW_KEY_1) == GLFW_PRESS || glfwGetKey(window,GLFW_KEY_KP_1) == GLFW_PRESS){
        if(mode != Modes::SMOOTH){
            mode = Modes::SMOOTH;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            normalV.clear();
            for(int i = 0;i < shapes.size();i++){
                std::vector<glm::vec3>temp = shapes[i]->getVertices();
                normalV.insert(normalV.end(),temp.begin(),temp.end());
            }
            glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
            glBufferData(GL_ARRAY_BUFFER, normalV.size() * sizeof(glm::vec3), normalV.data(), GL_STATIC_DRAW);
        }

    }
    if(glfwGetKey(window,GLFW_KEY_2) == GLFW_PRESS || glfwGetKey(window,GLFW_KEY_KP_2) == GLFW_PRESS){
        if(mode != Modes::FLAT){
            mode = Modes::FLAT;
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            normalV.clear();
            for(int i = 0;i < shapes.size();i++){
                std::vector<glm::vec3>temp = shapes[i]->getNormal();
                normalV.insert(normalV.end(),temp.begin(),temp.end());
            }
            glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
            glBufferData(GL_ARRAY_BUFFER, normalV.size() * sizeof(glm::vec3), normalV.data(), GL_STATIC_DRAW);
        }
    }
    if(glfwGetKey(window,GLFW_KEY_3) == GLFW_PRESS || glfwGetKey(window,GLFW_KEY_KP_3) == GLFW_PRESS){
        if(mode != Modes::WIREFRAME){
            mode = Modes::WIREFRAME;
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            normalV.clear();
            for(int i = 0;i < shapes.size();i++){
                std::vector<glm::vec3>temp = shapes[i]->getNormal();
                for(int i = 0;i < temp.size();i++){
                    glm::vec3 norm(0,0,0);
                    normalV.push_back(norm);
                }
            }
            glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
            glBufferData(GL_ARRAY_BUFFER, normalV.size() * sizeof(glm::vec3), normalV.data(), GL_STATIC_DRAW);
        }
    }
}

void processInputs(GLFWwindow * window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !flight)
    {
        camera.processKeyboard(CameraMovement::FORWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && !flight)
    {
        camera.processKeyboard(CameraMovement::BACKWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !flight)
    {
        camera.processKeyboard(CameraMovement::LEFT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !flight)
    {
        camera.processKeyboard(CameraMovement::RIGHT, deltaTime);
    }
}

void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        mousePressed = true;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        mousePressed = false;
    }
}

void cursorPosCallback(GLFWwindow * window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;  // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    if (mousePressed)
    {
        camera.processMouseMovement(xoffset, yoffset);
    }
}

void scrollCallback(GLFWwindow * window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
}
