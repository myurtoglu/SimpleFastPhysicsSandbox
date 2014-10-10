#include <memory>
#include "FixtureShape.hpp"
#include "BoxSfmlHelpers.hpp"


FixtureShape::FixtureShape(b2World & world, b2Vec2 initialPos, b2Vec2 size,
                           unsigned ySize, float PPM, sf::Color color)
: Shape(world, initialPos, ySize, PPM)
{
    mShape = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(size.x,size.y)));
    mShape->setFillColor(color);
    mShape->setOrigin(size.x/2.f, size.y/2.f);
    world.DestroyBody(mBody);
    mBodyDef.type = b2_staticBody;
    mBody = world.CreateBody(&mBodyDef);
    mBodyShape = std::unique_ptr<b2PolygonShape>(new b2PolygonShape());
    static_cast<b2PolygonShape*>(mBodyShape.get())->SetAsBox(size.x/(2*mPPM),
                                                             size.y/(2*mPPM));
    setBodyFix(0.3f, 0.5f, 0.25f);
    update();
}
