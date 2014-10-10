#ifndef FixtureShape_HPP_
#define FixtureShape_HPP_

#include "Shape.hpp"


class FixtureShape : public Shape
{
public:
    FixtureShape(b2World&, b2Vec2, b2Vec2, unsigned, float,
                 sf::Color color=sf::Color::Red);
};

#endif

