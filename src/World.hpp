#ifndef World_HPP_
#define World_HPP_

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Shape.hpp"
#include "ResourcePath.hpp"
#include <memory>
#include <list>


class World : private sf::NonCopyable
{
public:
        World(std::shared_ptr<sf::RenderWindow>, float, float, float, b2Vec2);
   void step(float, int, int);
   void draw();
   void destroyObject(b2Vec2);
   void setGravity(float);
   void setSize(float);
   void setActionType(int);
   void createObject(b2Vec2);
   void clear();
   int  getBodyCount();

private:
   void addRect(b2Vec2);
   void addCirc(b2Vec2);
   void addFixture(b2Vec2);
   void addPermanentFixture(b2Vec2, b2Vec2, sf::Color, unsigned);

private:

   float                                     thinEdgeThickness = 1.f;
   float                                     defaultShapeSize = 30.f;
   std::shared_ptr<sf::RenderWindow>         mWindow;
   std::list<std::unique_ptr<Shape>>         mDynamicShapes;
   std::list<std::unique_ptr<Shape>>         mStaticShapes;
   std::list<std::unique_ptr<Shape>>         mPermanentShapes;
   sf::Time                                  mStatisticsUpdateTime;
   b2World                                   mWorld;
   b2BodyDef                                 groundBodyDef;
   b2Body                                    *groundBody;
   b2BodyDef                                 bodyDef;
   b2FixtureDef                              fixtureDef;
   float                                     shapeSize;
   int                                       actiontype = 0;
   float                                     mPPM;
   float                                     mSeparatorRatio;
   float                                     mGroundHeight;
};

#endif
