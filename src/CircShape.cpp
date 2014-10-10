#include <memory>
#include "CircShape.hpp"
#include "BoxSfmlHelpers.hpp"


CircShape::CircShape(b2World &world, b2Vec2 initialPos, float radius,
                     unsigned ySize, float PPM): Shape(world, initialPos,
                                                       ySize, PPM)
{
    mShape = std::unique_ptr<sf::CircleShape>(new sf::CircleShape(radius));
    mShape->setFillColor(sf::Color::Blue);
    mShape->setOrigin(radius, radius);
    mBodyShape = std::unique_ptr<b2CircleShape>(new b2CircleShape());
    mBodyShape->m_radius = radius/mPPM;
    setBodyFix(0.3f, 0.5f, 0.25f);
    update();
}
