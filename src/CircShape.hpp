#ifndef CircShape_HPP_
#define CircShape_HPP_

#include "Shape.hpp"


class CircShape : public Shape
{
public:
    CircShape(b2World&, b2Vec2, float, unsigned, float);
};

#endif
