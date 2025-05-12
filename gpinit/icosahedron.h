#ifndef GPINIT_ICOSAHEDRON_H
#define GPINIT_ICOSAHEDRON_H

#include "gpinit/shape.h"


class Icosahedron : public Shape
{
public:
    Icosahedron(int depth)
    {
        for(int i = 0; i < NUM_FACETS;i++){
            glm::vec3 a(vertexData[3*i][0],vertexData[3*i][1],vertexData[3*i][2]);
            glm::vec3 b(vertexData[(3*i)+1][0],vertexData[(3*i)+1][1],vertexData[(3*i)+1][2]);
            glm::vec3 c(vertexData[(3*i)+2][0],vertexData[(3*i)+2][1],vertexData[(3*i)+2][2]);
            subdivide(a,b,c,depth);
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
            vertex.push_back(v1);
            vertex.push_back(v2);
            vertex.push_back(v3);
            float x = ((v1.x+v2.x+v3.x)/3);
            float y = ((v1.y+v2.y+v3.y)/3);
            float z = ((v1.z+v2.z+v3.z)/3);
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


#endif  // FLIGHT_ICOSAHEDRON_H
