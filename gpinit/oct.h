//
// Created by student on 4/20/21.
//

#ifndef GPINIT_OCT_H
#define GPINIT_OCT_H
#include "gpinit/shape.h"
#include "math.h"
class Oct : public Shape
{
public:
    Oct()
    {
        // TODO: set vertex and normal
        // The normal is associated with vertices, but it is facet normal, NOT vertex normal.
        // Please refer to shaders for details.
        for(int i = 0; i < NUM_FACETS;i++){
            glm::vec3 a(vertexData[3*i][0],vertexData[3*i][1],vertexData[3*i][2]);
            glm::vec3 b(vertexData[(3*i)+1][0],vertexData[(3*i)+1][1],vertexData[(3*i)+1][2]);
            glm::vec3 c(vertexData[(3*i)+2][0],vertexData[(3*i)+2][1],vertexData[(3*i)+2][2]);
            float x = ((a.x+b.x+c.x)/3);
            float y = ((a.y+b.y+c.y)/3);
            float z = ((a.z+b.z+c.z)/3);
            glm::vec3 norm(x,y,z);
            vertex.push_back(a);
            vertex.push_back(b);
            vertex.push_back(c);
            normal.push_back(norm);
            normal.push_back(norm);
            normal.push_back(norm);
        }

    }

    GLuint getNumVertices() const override
    {
        return NUM_VERTICES;
    }

    const glm::vec3 * getVertexData() const override
    {
        return vertex.data();
    }

    const glm::vec3 * getNormalData() const override
    {
        return normal.data();
    }
    const std::vector<glm::vec3> getVertices() const override
    {
        return vertex;
    }
    const std::vector<glm::vec3> getNormal() const override
    {
        return normal;
    }

private:
    // this is a special trick called "the enum hack"
    // to define class constants of integral type,
    // which is more favored than static constant members
    enum : GLuint
    {
        NUM_FACETS = 8 ,
        NUM_VERTICES = NUM_FACETS * 3
    };

    const GLfloat vertexData[NUM_VERTICES][3] =
            {
                    0.5f, 0.0f, 0.5f,
                    0.5f, 0.0f,-0.5f,
                    0.0f, float(sqrt(0.5f)), 0.0f,

                    0.5f, 0.0f, 0.5f,
                    0.5f, 0.0f,-0.5f,
                    0.0f,float(-sqrt(0.5f)), 0.0f,

                    0.5f, 0.0f,-0.5f,
                    -0.5f, 0.0f,-0.5f,
                    0.0f, float(sqrt(0.5f)), 0.0f,

                    0.5f, 0.0f,-0.5f,
                    -0.5f, 0.0f,-0.5f,
                    0.0f, float(-sqrt(0.5f)), 0.0f,

                    -0.5f, 0.0f,-0.5f,
                    -0.5f, 0.0f,0.5f,
                    0.0f, float(sqrt(0.5f)),0.0f,

                    -0.5f, 0.0f,-0.5f,
                    -0.5f, 0.0f,0.5f,
                    0.0f, float(-sqrt(0.5f)),0.0f,

                    -0.5f, 0.0f, 0.5f,
                    0.5f,  0.0f, 0.5f,
                    0.0f,float(sqrt(0.5f)), 0.0f,

                    -0.5f, 0.0f, 0.5f,
                    0.5f,  0.0f, 0.5f,
                    0.0f,float(-sqrt(0.5f)), 0.0f,
            };

    std::vector<glm::vec3> vertex;
    std::vector<glm::vec3> normal;
};
#endif //FLIGHT_OCT_H
