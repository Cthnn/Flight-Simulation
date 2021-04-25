//
// Created by student on 4/22/21.
//

#ifndef FLIGHT_ELLIPSOID_H
#define FLIGHT_ELLIPSOID_H
#include "flight/Shape.h"


class Ellipsoid : public Shape
{
public:
    Ellipsoid()
    {
        for(int i = 0; i < NUM_FACETS;i++){
            glm::vec3 a(vertexData[3*i][0],vertexData[3*i][1],vertexData[3*i][2]);
            glm::vec3 b(vertexData[(3*i)+1][0],vertexData[(3*i)+1][1],vertexData[(3*i)+1][2]);
            glm::vec3 c(vertexData[(3*i)+2][0],vertexData[(3*i)+2][1],vertexData[(3*i)+2][2]);
            subdivide(a,b,c,2);
        }
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
    enum : GLuint
    {
        NUM_FACETS = 20,
        NUM_VERTICES = NUM_FACETS * 3
    };

    const GLfloat X = .525731112119133606;
    const GLfloat Z = .850650808352039932;

    const GLfloat vertexData[NUM_VERTICES][3] =
            {
                    {X,   0.0,  Z}, {0.0, Z,    X}, {-X,  0.0,  Z},
                    {0.0, Z,    X}, {-Z,  X,  0.0}, {-X,  0.0,  Z},
                    {0.0, Z,    X}, {0.0, Z,   -X}, {-Z,  X,  0.0},
                    {Z,   X,  0.0}, {0.0, Z,   -X}, {0.0, Z,    X},
                    {X,   0.0,  Z}, {Z,   X,  0.0}, {0.0, Z,    X},
                    {X,   0.0,  Z}, {Z,   -X, 0.0}, {Z,   X,  0.0},
                    {Z,   -X, 0.0}, {X,   0.0, -Z}, {Z,   X,  0.0},
                    {Z,   X,  0.0}, {X,   0.0, -Z}, {0.0, Z,   -X},
                    {X,   0.0, -Z}, {-X,  0.0, -Z}, {0.0, Z,   -X},
                    {X,   0.0, -Z}, {0.0, -Z,  -X}, {-X,  0.0, -Z},
                    {X,   0.0, -Z}, {Z,   -X, 0.0}, {0.0, -Z,  -X},
                    {Z,   -X, 0.0}, {0.0, -Z,   X}, {0.0, -Z,  -X},
                    {0.0, -Z,   X}, {-Z,  -X, 0.0}, {0.0, -Z,  -X},
                    {0.0, -Z,   X}, {-X,  0.0,  Z}, {-Z,  -X, 0.0},
                    {0.0, -Z,   X}, {X,   0.0,  Z}, {-X,  0.0,  Z},
                    {Z,   -X, 0.0}, {X,   0.0,  Z}, {0.0, -Z,   X},
                    {-Z,  -X, 0.0}, {-X,  0.0,  Z}, {-Z,  X,  0.0},
                    {-X,  0.0, -Z}, {-Z,  -X, 0.0}, {-Z,  X,  0.0},
                    {0.0, Z,   -X}, {-X,  0.0, -Z}, {-Z,  X,  0.0},
                    {-Z,  -X, 0.0}, {-X,  0.0, -Z}, {0.0, -Z,  -X}
            };

    std::vector<glm::vec3> vertex;
    std::vector<glm::vec3> normal;
    void subdivide(const glm::vec3 & v1, const glm::vec3 & v2, const glm::vec3 & v3, unsigned long depth)
    {
        if (depth == 0)
        {
            glm::vec3 a(v1.x*3,v1.y,v1.z);
            glm::vec3 b(v2.x*3,v2.y,v2.z);
            glm::vec3 c(v3.x*3,v3.y,v3.z);
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
#endif //FLIGHT_ELLIPSOID_H
