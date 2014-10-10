#ifndef RectShape_HPP_
#define RectShape_HPP_

#include "Shape.hpp"


class RectShape : public Shape
{
public:
    RectShape(b2World&, b2Vec2, b2Vec2, unsigned, float);
};

#endif
