#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include <memory>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>


class Shape
{
public:
                Shape(b2World&, b2Vec2, unsigned, float);
    b2Body*     getBody();
    sf::Shape&  getShape();
    void        update();
    void        setBodyFix(float, float, float);
    virtual ~Shape() = default;

protected:
    b2Body                     *mBody;
    float                      mPPM;
    int                        mYSize;
    std::unique_ptr<sf::Shape> mShape;
    b2BodyDef                  mBodyDef;
    std::unique_ptr<b2Shape>   mBodyShape;
    b2FixtureDef               mBodyFix;
};

#endif
