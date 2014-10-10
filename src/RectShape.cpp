#include <memory>
#include "RectShape.hpp"
#include "BoxSfmlHelpers.hpp"


RectShape::RectShape(b2World &world, b2Vec2 initialPos, b2Vec2 size,
                     unsigned ySize, float PPM)
: Shape(world, initialPos, ySize, PPM)
{
    mShape = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(size.x,size.y)));
    mShape->setFillColor(sf::Color::Red);
    mShape->setOrigin(size.x/2.f, size.y/2.f);
    mBodyShape = std::unique_ptr<b2PolygonShape>(new b2PolygonShape());
    static_cast<b2PolygonShape*>(mBodyShape.get())->SetAsBox(size.x/(2*mPPM),
                                                             size.y/(2*mPPM));
    setBodyFix(0.3f, 0.5f, 0.25f);
    update();
}
