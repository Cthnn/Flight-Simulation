#ifndef GPINIT_SHAPE_H
#define GPINIT_SHAPE_H

#include <glad/glad.h>
#include <glm/glm.hpp>


// An abstract class to represent generic shapes,
// just consider it a Java interface if you are new to C++ polymorphism.
// An "= 0;" says that the function is pure virtual and there will be no definition
// (just like APIs in Java interfaces).
class Shape
{
public:
    virtual GLuint getNumVertices() const = 0;

    virtual const glm::vec3 * getVertexData() const = 0;

    virtual const glm::vec3 * getNormalData() const = 0;
    virtual const std::vector<glm::vec3> getVertices() const = 0;
    virtual const std::vector<glm::vec3> getNormal() const = 0;
};



#endif  // FLIGHT_SHAPE_H
