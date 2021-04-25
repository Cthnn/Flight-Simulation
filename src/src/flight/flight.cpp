#include <bits/stdc++.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "other/camera.h"
#include "other/shader.h"
#include "flight/Cube.h"
#include "flight/Tetra.h"
#include "flight/Oct.h"
#include "flight/Cylinder.h"
#include "flight/Cone.h"
#include "flight/Torus.h"
#include "flight/Ellipsoid.h"
#include "flight/Dodecahedron.h"
#include "flight/Icosahedron.h"

// Method Headers
void framebufferSizeCallback(GLFWwindow * window, int width, int height);
void cursorPosCallback(GLFWwindow * window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInputs(GLFWwindow * window);
void perFrameTimeLogic();
void scrollCallback(GLFWwindow * window, double xoffset, double yoffset);


// Set Window Height and width
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 1024;

//Shape Display Modes
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
glm::vec3 lightPos(0.0f, 0.0f, 5.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 objColor(0.0f, 0.0f, 1.0f);

//Defining the shapes in the universe and their positions.
std::vector<Shape*> shapes = {new Cone,new Cube(),new Cylinder(),new Ellipsoid(),new Icosahedron(0),new Icosahedron(2),new Oct(),new Tetra(),new Torus(), new Dodecahedron()};
std::vector<std::vector<GLuint>>indices;
std::vector<glm::vec3> vertices;
std::vector<glm::vec3> normalV;
std::vector<float>rot;
glm::vec3 shapePos[] = {glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(2.0f, 5.0f, -15.0f),glm::vec3(-1.5f, -5.2f, -2.5f),glm::vec3(-3.8f, -2.0f, -12.3f),glm::vec3(2.4f, -0.4f, -10.5f),glm::vec3(-0.7f, 3.0f, -7.5f),glm::vec3(1.3f, -3.0f, -9.0f),glm::vec3(2.8f, 2.0f, -2.5f),glm::vec3(1.7f, 0.3f, -20.0f),glm::vec3(4.5f, -7.0f, -12.0f)};
// Variables for Flight Simulation
bool flight = false;
bool vertical = true;
//Init camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
glm::vec3 center;
int curr = 0;
int rad = 17.7;
GLuint normalVBO;

int main()
{
    // For Random Rotations, Initialize random seed
    unsigned seed = time(0);
    srand(seed);

    // Get Center of the Universe
    float center_x= 0,center_y=0,center_z=0;
    for(int i = 0;i< shapes.size();i++){
        center_x += shapePos[i].x;
        center_y += shapePos[i].y;
        center_z += shapePos[i].z;
    }
    center_x = center_x/shapes.size();
    center_y = center_y/shapes.size();
    center_z = center_z/shapes.size();
    center = glm::vec3(center_x,center_y,center_z);

    //Initialize Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGLDemo", nullptr, nullptr);

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
    //If mode is WIREFRAME mode, just show lines
    if(mode == Modes::WIREFRAME){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    // Adds  Vertices to a combined array and Normals to a combined normal arrays
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


    Shader shader("./src/shader/phong.vert.glsl", "./src/shader/phong.frag.glsl");
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


    glGenBuffers(1, &normalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glBufferData(GL_ARRAY_BUFFER, normalV.size() * sizeof(glm::vec3), normalV.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void *>(0));

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    while (!glfwWindowShouldClose(window))
    {
        //For flight simulation. Circles around the universe based on "curr" which represents the start time of the flight simulation
        if(flight){
            if(vertical){
                glm::vec3 camPos(center.x,center.y+rad*sin(M_PI*(1000-curr)/1000),center.z-rad*cos(M_PI*(1000-curr)/1000));
                camera.changePos(camPos);
                curr+=1;
            }else{
                glm::vec3 camPos(center.x+rad*sin(M_PI*(1000-curr)/1000),center.y,center.z-rad*cos(M_PI*(1000-curr)/1000));
                camera.changePos(camPos);
                curr+=1;
            }

        }
        perFrameTimeLogic();
        processInputs(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        // Pass parameters into our shaders
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,100.0f);
        shader.setMat4("projection",projection);
        glm::mat4 view = camera.getViewMatrix();
        shader.setMat4("view", view);
        shader.setVec3("lightPos",lightPos);
        shader.setVec3("viewPos",camera.Position);
        shader.setVec3("lightColor",lightColor);
        shader.setVec3("objectColor",objColor);

        // Get info associated with each shape and draw the shape
        for(int i=0; i < shapes.size();i++){
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, shapePos[i]);
            model = glm::rotate(model, glm::radians(rot[i]), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, indices[i][0], indices[i][1]);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &normalVBO);
    glDeleteProgram(shader.getShaderProgramHandle());
    glfwTerminate();

    return 0;
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


void perFrameTimeLogic()
{
    auto currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
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


