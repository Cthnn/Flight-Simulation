//
// Created by student on 4/21/21.
//

#ifndef FLIGHT_CONE_H
#define FLIGHT_CONE_H
#include "flight/Shape.h"
#include "math.h"

class Cone : public Shape
{
public:
    Cone()
    {
        for(int i = 0; i < NUM_FACETS;i++){
            glm::vec3 a(vertexData[3*i][0],vertexData[3*i][1],vertexData[3*i][2]);
            glm::vec3 b(vertexData[(3*i)+1][0],vertexData[(3*i)+1][1],vertexData[(3*i)+1][2]);
            glm::vec3 c(vertexData[(3*i)+2][0],vertexData[(3*i)+2][1],vertexData[(3*i)+2][2]);
            vertex.push_back(a);
            vertex.push_back(b);
            vertex.push_back(c);
            if(i%2 == 0){
                glm::vec3 norm(0,1,0);
                normal.push_back(norm);
                normal.push_back(norm);
                normal.push_back(norm);
            }else{
                float x = ((a.x+b.x+c.x)/3);
                float y = ((a.y+b.y+c.y)/3);
                float z = ((a.z+b.z+c.z)/3);
                glm::vec3 norm(x,y,z);
                normal.push_back(norm);
                normal.push_back(norm);
                normal.push_back(norm);
            }


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
        NUM_SECTORS = 16,
        NUM_FACETS = (16*2),
        NUM_VERTICES = NUM_FACETS * 3
    };

    const GLfloat angle = 2*M_PI/16;

    const GLfloat vertexData[NUM_VERTICES][3] =
            {
                    {0.5f*cos(angle*0),   0.5f,  0.5f*sin(angle*0)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*1),   0.5f,  0.5f*sin(angle*1)},
                    {0.5f*cos(angle*0),   0.5f,  0.5f*sin(angle*0)},{0.5f*cos(angle*1),   0.5f,  0.5f*sin(angle*1)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*1),   0.5f,  0.5f*sin(angle*1)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*2),   0.5f,  0.5f*sin(angle*2)},
                    {0.5f*cos(angle*1),   0.5f,  0.5f*sin(angle*1)},{0.5f*cos(angle*2),   0.5f,  0.5f*sin(angle*2)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*2),   0.5f,  0.5f*sin(angle*2)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*3),   0.5f,  0.5f*sin(angle*3)},
                    {0.5f*cos(angle*2),   0.5f,  0.5f*sin(angle*2)},{0.5f*cos(angle*3),   0.5f,  0.5f*sin(angle*3)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*3),   0.5f,  0.5f*sin(angle*3)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*4),   0.5f,  0.5f*sin(angle*4)},
                    {0.5f*cos(angle*3),   0.5f,  0.5f*sin(angle*3)},{0.5f*cos(angle*4),   0.5f,  0.5f*sin(angle*4)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*4),   0.5f,  0.5f*sin(angle*4)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*5),   0.5f,  0.5f*sin(angle*5)},
                    {0.5f*cos(angle*4),   0.5f,  0.5f*sin(angle*4)},{0.5f*cos(angle*5),   0.5f,  0.5f*sin(angle*5)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*5),   0.5f,  0.5f*sin(angle*5)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*6),   0.5f,  0.5f*sin(angle*6)},
                    {0.5f*cos(angle*5),   0.5f,  0.5f*sin(angle*5)},{0.5f*cos(angle*6),   0.5f,  0.5f*sin(angle*6)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*6),   0.5f,  0.5f*sin(angle*6)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*7),   0.5f,  0.5f*sin(angle*7)},
                    {0.5f*cos(angle*6),   0.5f,  0.5f*sin(angle*6)},{0.5f*cos(angle*7),   0.5f,  0.5f*sin(angle*7)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*7),   0.5f,  0.5f*sin(angle*7)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*8),   0.5f,  0.5f*sin(angle*8)},
                    {0.5f*cos(angle*7),   0.5f,  0.5f*sin(angle*7)},{0.5f*cos(angle*8),   0.5f,  0.5f*sin(angle*8)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*8),   0.5f,  0.5f*sin(angle*8)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*9),   0.5f,  0.5f*sin(angle*9)},
                    {0.5f*cos(angle*8),   0.5f,  0.5f*sin(angle*8)},{0.5f*cos(angle*9),   0.5f,  0.5f*sin(angle*9)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*9),   0.5f,  0.5f*sin(angle*9)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*10),   0.5f,  0.5f*sin(angle*10)},
                    {0.5f*cos(angle*9),   0.5f,  0.5f*sin(angle*9)},{0.5f*cos(angle*10),   0.5f,  0.5f*sin(angle*10)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*10),   0.5f,  0.5f*sin(angle*10)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*11),   0.5f,  0.5f*sin(angle*11)},
                    {0.5f*cos(angle*10),   0.5f,  0.5f*sin(angle*10)},{0.5f*cos(angle*11),   0.5f,  0.5f*sin(angle*11)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*11),   0.5f,  0.5f*sin(angle*11)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*12),   0.5f,  0.5f*sin(angle*12)},
                    {0.5f*cos(angle*11),   0.5f,  0.5f*sin(angle*11)},{0.5f*cos(angle*12),   0.5f,  0.5f*sin(angle*12)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*12),   0.5f,  0.5f*sin(angle*12)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*13),   0.5f,  0.5f*sin(angle*13)},
                    {0.5f*cos(angle*12),   0.5f,  0.5f*sin(angle*12)},{0.5f*cos(angle*13),   0.5f,  0.5f*sin(angle*13)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*13),   0.5f,  0.5f*sin(angle*13)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*14),   0.5f,  0.5f*sin(angle*14)},
                    {0.5f*cos(angle*13),   0.5f,  0.5f*sin(angle*13)},{0.5f*cos(angle*14),   0.5f,  0.5f*sin(angle*14)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*14),   0.5f,  0.5f*sin(angle*14)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*15),   0.5f,  0.5f*sin(angle*15)},
                    {0.5f*cos(angle*14),   0.5f,  0.5f*sin(angle*14)},{0.5f*cos(angle*15),   0.5f,  0.5f*sin(angle*15)},{0,   -0.5f,  0},

                    {0.5f*cos(angle*15),   0.5f,  0.5f*sin(angle*15)},{0.0f,0.5f,0.0f},{0.5f*cos(angle*0),   0.5f,  0.5f*sin(angle*0)},
                    {0.5f*cos(angle*15),   0.5f,  0.5f*sin(angle*15)},{0.5f*cos(angle*0),   0.5f,  0.5f*sin(angle*0)},{0,   -0.5f,  0}
            };

    std::vector<glm::vec3> vertex;
    std::vector<glm::vec3> normal;
};
#endif //FLIGHT_CONE_H
