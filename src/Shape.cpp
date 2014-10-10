#include "Shape.hpp"
#include "BoxSfmlHelpers.hpp"


Shape::Shape(b2World &world, b2Vec2 initialPos, unsigned ySize, float PPM)
: mPPM(PPM)
, mYSize(ySize)
{
    mBodyDef.position.Set(initialPos.x, initialPos.y);
    mBodyDef.type = b2_dynamicBody;
    mBody = world.CreateBody(&mBodyDef);
}


b2Body* Shape::getBody()
{
    return mBody;
}


sf::Shape& Shape::getShape()
{
    return *mShape;
}


void Shape::update()
{
    mShape->setPosition(ConvB2VecToSff(mBody->GetPosition(), mYSize, mPPM));
    mShape->setRotation(-mBody->GetAngle()*180.f/M_PI);
}


void Shape::setBodyFix(float density, float friction, float restitution)
{
    mBodyFix.shape = mBodyShape.get();
    mBodyFix.density = density;
    mBodyFix.friction = friction;
    mBodyFix.restitution = restitution;
    mBody->CreateFixture(&mBodyFix);
}
