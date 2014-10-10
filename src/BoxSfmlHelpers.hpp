#ifndef BoxSfmlHelpers_HPP_
#define BoxSfmlHelpers_HPP_

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

// template function to convert sfml vectors to box2d vectors
template <typename T>
inline b2Vec2 ConvSfToB2Vec(const sf::Vector2<T>&, int, float);

// box2d vectors to sfml vectors (float)
inline sf::Vector2f ConvB2VecToSff(const b2Vec2&, int, float);

// box2d vectors to sfml vectors (integer)
inline sf::Vector2i ConvB2VecToSfi(const b2Vec2&, int, float);

#include "BoxSfmlHelpers.inl"

#endif
