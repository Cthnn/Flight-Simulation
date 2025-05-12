#ifndef GPINIT_WORLD_H
#define GPINIT_WORLD_H

#include <bits/stdc++.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "gpinit/camera.h"
#include "gpinit/shader.h"
#include "gpinit/shape.h"
#include <vector>


glm::vec3 get_center(std::vector<glm::vec3> shapePos){
    // Get Center of the Universe
    float center_x= 0,center_y=0,center_z=0;
    for(int i = 0;i< shapePos.size();i++){
        center_x += shapePos[i].x;
        center_y += shapePos[i].y;
        center_z += shapePos[i].z;
    }
    center_x = center_x/shapePos.size();
    center_y = center_y/shapePos.size();
    center_z = center_z/shapePos.size();
    return glm::vec3(center_x,center_y,center_z);
}

void pass_params_to_shader(Shader shader, Camera camera, unsigned int screenWidth, unsigned int screenHeight,
                            glm::vec3 lightPos, glm::vec3 lightColor, glm::vec3 objColor, std::vector<Shape*> shapes,
                            std::vector<glm::vec3> shapePos, std::vector<std::vector<GLuint>>indices, std::vector<float>rot){
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) screenWidth / (float) screenHeight, 0.1f,100.0f);
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
}
#endif