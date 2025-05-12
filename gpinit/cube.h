#ifndef GPINIT_CUBE_H
#define GPINIT_CUBE_H

#include "gpinit/shape.h"


class Cube : public Shape
{
public:
    Cube()
    {
        // TODO: set vertex and normal    
        // The normal is associated with vertices, but it is facet normal, NOT vertex normal. 
        // Please refer to shaders for details.
        for(int i = 0; i < NUM_FACETS;i++){
            glm::vec3 a(vertexData[3*i][0],vertexData[3*i][1],vertexData[3*i][2]);
            glm::vec3 b(vertexData[(3*i)+1][0],vertexData[(3*i)+1][1],vertexData[(3*i)+1][2]);
            glm::vec3 c(vertexData[(3*i)+2][0],vertexData[(3*i)+2][1],vertexData[(3*i)+2][2]);
            glm::vec3 vect1(a.x-b.x,a.y-b.y,a.z-b.z);
            glm::vec3 vect2(a.x-c.x,a.y-c.y,a.z-c.z);
            glm::vec3 norm(float(int(vect1.y*vect2.z-vect1.z*vect2.y)),float(int(vect1.x*vect2.z-vect1.z*vect2.x)),float(int(vect1.x*vect2.y-vect1.y*vect2.x)));
            if(norm.x != 0){
                if(a.x >= 0){
                    norm.x = float(abs(norm.x));
                }else{
                    norm.x = float(-abs(norm.x));
                }
            }
            if(norm.y != 0){
                if(a.y >= 0){
                    norm.y = float(abs(norm.y));
                }else{
                    norm.y = float(-abs(norm.y));
                }
            }
            if(norm.z != 0){
                if(a.z >= 0){
                    norm.z = float(abs(norm.z));
                }else{
                    norm.z = float(-abs(norm.z));
                }
            }
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
        NUM_FACETS = 6 * 2,
        NUM_VERTICES = NUM_FACETS * 3
    };

    const GLfloat vertexData[NUM_VERTICES][3] =
            {
                    -0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f,
                    0.5f,  0.5f, -0.5f,
                    0.5f,  0.5f, -0.5f,
                    -0.5f,  0.5f, -0.5f,
                    -0.5f, -0.5f, -0.5f,

                    -0.5f, -0.5f,  0.5f,
                    0.5f, -0.5f,  0.5f,
                    0.5f,  0.5f,  0.5f,
                    0.5f,  0.5f,  0.5f,
                    -0.5f,  0.5f,  0.5f,
                    -0.5f, -0.5f,  0.5f,

                    -0.5f,  0.5f,  0.5f,
                    -0.5f,  0.5f, -0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f, -0.5f,
                    -0.5f, -0.5f,  0.5f,
                    -0.5f,  0.5f,  0.5f,

                    0.5f,  0.5f,  0.5f,
                    0.5f,  0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f,  0.5f,
                    0.5f,  0.5f,  0.5f,

                    -0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f, -0.5f,
                    0.5f, -0.5f,  0.5f,
                    0.5f, -0.5f,  0.5f,
                    -0.5f, -0.5f,  0.5f,
                    -0.5f, -0.5f, -0.5f,

                    -0.5f,  0.5f, -0.5f,
                    0.5f,  0.5f, -0.5f,
                    0.5f,  0.5f,  0.5f,
                    0.5f,  0.5f,  0.5f,
                    -0.5f,  0.5f,  0.5f,
                    -0.5f,  0.5f, -0.5f,
            };

    std::vector<glm::vec3> vertex;
    std::vector<glm::vec3> normal;
};


#endif // FLIGHT_CUBE_H
