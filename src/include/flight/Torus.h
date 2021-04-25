//
// Created by student on 4/22/21.
//

#ifndef FLIGHT_TORUS_H
#define FLIGHT_TORUS_H
#include "flight/Shape.h"
#include "math.h"
class Torus : public Shape
{
public:
    Torus() {
        int ind1 = 0; int ind2 = 0;
        int count = 0;
        GLfloat r = 0.5, axial = 1.0;
        int segments = 25;
        for (int i = 0; i < segments; i++) {
            for (int j = 0; j < segments; j++) {
                for(int k =0;k<=1;k++){
                    GLfloat segNum1 = 0.5f+ ((i + k) % segments);
                    GLfloat segNum2 = j % (segments + 1);

                    GLfloat x = (axial + r * cos(segNum1 * 2*M_PI / segments)) * cos(segNum2 * 2*M_PI / segments);
                    GLfloat y = (axial + r * cos(segNum1 * 2*M_PI / segments)) * sin(segNum2 * 2*M_PI / segments);
                    GLfloat z = r * sin(segNum1 * 2*M_PI / segments);

                    glm::vec3 vert(x, y, z);
                    glm::vec3 norm = glm::normalize(vert);
                    count+=1;
                    if (count > 3){
                        glm::vec3 v1 = vertex[vertex.size()-2];
                        glm::vec3 v2 = vertex[vertex.size()-1];
                        vertex.push_back(v1);
                        vertex.push_back(v2);
                        normal.push_back(norm);
                        normal.push_back(norm);
                    }
                    vertex.push_back(vert);
                    normal.push_back(norm);
                    if(count == (segments*2)-1){
                        ind1 = vertex.size()-1;
                    }
                    if(count == (segments*2*(segments-1))){
                        ind2 = vertex.size()-1;
                    }
                    if (count == segments*2){
                        glm::vec3 first = vertex[0];
                        glm::vec3 second = vertex[1];
                        glm::vec3 slast = vertex[vertex.size()-2];
                        glm::vec3 last = vertex[vertex.size()-1];
                        vertex.push_back(first);
                        vertex.push_back(second);
                        vertex.push_back(slast);
                        vertex.push_back(second);
                        vertex.push_back(slast);
                        vertex.push_back(last);
                        normal.push_back(norm);
                        normal.push_back(norm);
                        normal.push_back(norm);
                        normal.push_back(norm);
                        normal.push_back(norm);
                        normal.push_back(norm);
                    }
                }
            }
        }
        glm::vec3 a = vertex[ind2];
        glm::vec3 b = vertex[ind1];
        glm::vec3 c = vertex[0];
        glm::vec3 norm = glm::normalize(a);
        vertex.push_back(a);
        vertex.push_back(b);
        vertex.push_back(c);
        normal.push_back(norm);
        normal.push_back(norm);
        normal.push_back(norm);
    }

    GLuint getNumVertices() const override
    {
        return vertex.size();
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


    std::vector<glm::vec3> vertex;
    std::vector<glm::vec3> normal;
    void subdivide(const glm::vec3 & v1, const glm::vec3 & v2, const glm::vec3 & v3, unsigned long depth)
    {
        if (depth == 0)
        {
            glm::vec3 a(v1.x,v1.y,v1.z);
            glm::vec3 b(v2.x,v2.y,v2.z);
            glm::vec3 c(v3.x,v3.y,v3.z);
            vertex.push_back(a);
            vertex.push_back(b);
            vertex.push_back(c);
            float x = ((a.x+b.x+c.x)/3);
            float y = ((a.y+b.y+c.y)/3);
            float z = ((a.z+b.z+c.z)/3);
            glm::vec3 norm(x,y,z);
            normal.push_back(norm);
            normal.push_back(norm);
            normal.push_back(norm);
            return;
        }

        glm::vec3 v12 = glm::normalize((v1 + v2) / 2.0f);
        glm::vec3 v23 = glm::normalize((v2 + v3) / 2.0f);
        glm::vec3 v31 = glm::normalize((v3 + v1) / 2.0f);
        subdivide(v1, v12, v31, depth - 1);
        subdivide(v2, v23, v12, depth - 1);
        subdivide(v3, v31, v23, depth - 1);
        subdivide(v12, v23, v31, depth - 1);
    }
};
#endif //FLIGHT_TORUS_H
