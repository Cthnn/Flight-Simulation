//
// Created by student on 4/24/21.
//

#ifndef FLIGHT_DODECAHEDRON_H
#define FLIGHT_DODECAHEDRON_H
#include "flight/Shape.h"
#include "math.h"


class Dodecahedron : public Shape
{
public:
    Dodecahedron()
    {
        for(int i = 0; i < NUM_FACETS;i++){
            glm::vec3 a(vertexData[3*i][0],vertexData[3*i][1],vertexData[3*i][2]);
            glm::vec3 b(vertexData[(3*i)+1][0],vertexData[(3*i)+1][1],vertexData[(3*i)+1][2]);
            glm::vec3 c(vertexData[(3*i)+2][0],vertexData[(3*i)+2][1],vertexData[(3*i)+2][2]);
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
        NUM_FACETS = 12*3,
        NUM_VERTICES = NUM_FACETS * 3
    };

    const GLfloat X = 1.0;
    const GLfloat PHI = (1+sqrt(5))/2;

    const GLfloat vertexData[NUM_VERTICES][3] =
            {
                    {0.0, PHI, X/PHI}, {X, X, X},{X/PHI, 0.0, PHI},
                    {0.0,  PHI, X/PHI}, {X/PHI, 0.0, PHI}, {-X/PHI, 0.0, PHI},
                    {0.0,  PHI, X/PHI}, {-X/PHI, 0.0, PHI},{-X, X, X},

                    {-X, X, X},{-X/PHI, 0.0, PHI},{-X,-X,X},
                    {-X, X, X},{-X,-X,X},{-PHI,-X/PHI,0.0},
                    {-X, X, X},{-PHI,-X/PHI,0.0},{-PHI,X/PHI,0.0},

                    {-PHI,X/PHI,0.0},{-PHI,-X/PHI,0.0},{-X,-X,-X},
                    {-PHI,X/PHI,0.0},{-X,-X,-X},{-X/PHI,0.0,-PHI},
                    {-PHI,X/PHI,0.0},{-X/PHI,0.0,-PHI},{-X,X,-X},

                    {-X,X,-X},{-X/PHI,0.0,-PHI},{X/PHI,0.0,-PHI},
                    {-X,X,-X},{X/PHI,0.0,-PHI},{X,X,-X},
                    {-X,X,-X},{X,X,-X},{0.0,PHI,-X/PHI},

                    {0.0,PHI,-X/PHI},{X,X,-X},{PHI,X/PHI,0.0},
                    {0.0,PHI,-X/PHI},{PHI,X/PHI,0.0},{X,X,X},
                    {0.0,PHI,-X/PHI},{X,X,X},{0.0, PHI, X/PHI},

                    {0.0,PHI,-X/PHI},{0.0, PHI, X/PHI},{-X, X, X},
                    {0.0,PHI,-X/PHI},{-X, X, X},{-PHI,X/PHI,0.0},
                    {0.0,PHI,-X/PHI},{-PHI,X/PHI,0.0},{-X,X,-X},

                    {X,X,X},{PHI,X/PHI,0.0},{PHI,-X/PHI,0.0},
                    {X,X,X},{PHI,-X/PHI,0.0},{X,-X,X},
                    {X,X,X},{X,-X,X},{X/PHI,0.0,PHI},

                    {X/PHI,0.0,PHI},{X,-X,X},{0.0,-PHI,X/PHI},
                    {X/PHI,0.0,PHI},{0.0,-PHI,X/PHI},{-X,-X,X},
                    {X/PHI,0.0,PHI},{-X,-X,X},{-X/PHI,0.0,PHI},

                    {-X,-X,X},{0.0,-PHI,X/PHI},{0.0,-PHI,-X/PHI},
                    {-X,-X,X},{0.0,-PHI,-X/PHI},{-X,-X,-X},
                    {-X,-X,X},{-X,-X,-X},{-PHI,-X/PHI,0.0},

                    {-X/PHI,0.0,-PHI},{-X,-X,-X},{0,-PHI,-X/PHI},
                    {-X/PHI,0.0,-PHI},{0,-PHI,-X/PHI},{X,-X,-X},
                    {-X/PHI,0.0,-PHI},{X,-X,-X},{X/PHI,0.0,-PHI},

                    {X/PHI,0.0,-PHI},{X,-X,-X},{PHI,-X/PHI,0.0},
                    {X/PHI,0.0,-PHI},{PHI,-X/PHI,0.0},{PHI,X/PHI,0.0},
                    {X/PHI,0.0,-PHI},{PHI,X/PHI,0.0},{X,X,-X},

                    {X,-X,-X},{PHI,-X/PHI,0.0},{X,-X,X},
                    {X,-X,-X},{X,-X,X},{0.0,-PHI,X/PHI},
                    {X,-X,-X},{0.0,-PHI,X/PHI},{0.0,-PHI,-X/PHI}



            };

    std::vector<glm::vec3> vertex;
    std::vector<glm::vec3> normal;

};
#endif //FLIGHT_DODECAHEDRON_H
