#include <algorithm>
#include <functional>
#include <iterator>
#include "BoxSfmlHelpers.hpp"
#include "CircShape.hpp"
#include "FixtureShape.hpp"
#include "RectShape.hpp"
#include "World.hpp"

using std::shared_ptr;
using std::unique_ptr;
using std::mem_fn;
using std::for_each;
using std::begin;
using std::end;

World::World(shared_ptr<sf::RenderWindow> window, float PPM,
             float separatorRatio, float groundHeight, b2Vec2 gravity)
: mWindow(window)
, mWorld(gravity)
, shapeSize(defaultShapeSize)
, mPPM(PPM)
, mSeparatorRatio(separatorRatio)
, mGroundHeight(groundHeight)
{
    groundBody = mWorld.CreateBody(&groundBodyDef);

    // bottom edge
    sf::Vector2f pos = {(mWindow->getSize().x * mSeparatorRatio)/2,
                        (mWindow->getSize().y - mGroundHeight/2)};

    b2Vec2 size = {mWindow->getSize().x * mSeparatorRatio, mGroundHeight};

    addPermanentFixture(ConvSfToB2Vec(pos, mWindow->getSize().y, PPM),
                        size, {120, 200, 120}, mWindow->getSize().y);

    // right edge
    pos = {mWindow->getSize().x * mSeparatorRatio + thinEdgeThickness/2,
           static_cast<float>(mWindow->getSize().y / 2)};

    size = {thinEdgeThickness, static_cast<float>(mWindow->getSize().y)};

    addPermanentFixture(ConvSfToB2Vec(pos, mWindow->getSize().y, PPM),
                        size, {120, 200, 120}, mWindow->getSize().y);

    // left edge
    pos = {thinEdgeThickness/2, static_cast<float>(mWindow->getSize().y / 2)};

    size = {thinEdgeThickness, static_cast<float>(mWindow->getSize().y)};

    addPermanentFixture(ConvSfToB2Vec(pos, mWindow->getSize().y, PPM),
                        size, {120, 200, 120}, mWindow->getSize().y);

    // top edge
    pos = {(mWindow->getSize().x * mSeparatorRatio)/2,
           (thinEdgeThickness/2)};

    size = {mWindow->getSize().x * mSeparatorRatio, thinEdgeThickness};

    addPermanentFixture(ConvSfToB2Vec(pos, mWindow->getSize().y, PPM),
                        size, {120, 200, 120}, mWindow->getSize().y);
}


void World::step(float timeStep, int velocityIterations,
                 int positionIterations)
{
    mWorld.Step(timeStep, velocityIterations, positionIterations);
    auto shape_update = mem_fn(&Shape::update);
    for_each(begin(mDynamicShapes), end(mDynamicShapes), shape_update);
}


void World::draw()
{
    for_each(mDynamicShapes.cbegin(), mDynamicShapes.cend(),
             [this](decltype(*mDynamicShapes.cbegin()) &el)
    {
        mWindow->draw(el->getShape());
    });

    for_each(mStaticShapes.cbegin(), mStaticShapes.cend(),
             [this](decltype(*mStaticShapes.cbegin()) &el)
    {
        mWindow->draw(el->getShape());
    });

    for_each(mPermanentShapes.cbegin(), mPermanentShapes.cend(),
             [this](decltype(*mPermanentShapes.cbegin()) &el)
    {
        mWindow->draw(el->getShape());
    });
}


void World::addRect(b2Vec2 initpos)
{
    auto rect = new RectShape(mWorld, initpos, {shapeSize, shapeSize},
                              mWindow->getSize().y, mPPM);
    mDynamicShapes.push_back(unique_ptr<Shape>(rect));
}


void World::addCirc(b2Vec2 initpos)
{
    auto circ = new CircShape(mWorld, initpos, shapeSize,
                              mWindow->getSize().y, mPPM);
    mDynamicShapes.push_back(unique_ptr<Shape>(circ));
}


void World::addFixture(b2Vec2 initpos)
{
    auto fixture = new FixtureShape(mWorld, initpos, {shapeSize, 10},
                                    mWindow->getSize().y, mPPM,
                                    sf::Color::Yellow);
    fixture->getShape().setPosition(ConvB2VecToSff(fixture->getBody()->GetPosition(),
                                                   mWindow->getSize().y, mPPM));

    fixture->getShape().setRotation(-fixture->getBody()->GetAngle()*180.f/M_PI);
    mStaticShapes.push_back(unique_ptr<FixtureShape>(fixture));
}


void World::addPermanentFixture(b2Vec2 initpos, b2Vec2 size, sf::Color color,
                                unsigned ySize)
{
    auto fixture = new FixtureShape(mWorld, initpos, size, ySize,
                                    mPPM, color);
    fixture->getShape().setPosition(ConvB2VecToSff(fixture->getBody()->GetPosition(),
                                                   mWindow->getSize().y, mPPM));

    fixture->getShape().setRotation(-fixture->getBody()->GetAngle()*180.f/M_PI);
    mPermanentShapes.push_back(unique_ptr<FixtureShape>(fixture));
}


void World::destroyObject(b2Vec2 position)
{
    auto pos = ConvB2VecToSff(position, mWindow->getSize().y, mPPM);

    for (auto &el : mDynamicShapes) {
        if (el->getShape().getGlobalBounds().contains(pos)) {
            mWorld.DestroyBody(el->getBody());
            mDynamicShapes.remove(el);
            break;
        }
    }

    for (auto &el : mStaticShapes) {
        if (el->getShape().getGlobalBounds().contains(pos)) {
            mWorld.DestroyBody(el->getBody());
            mStaticShapes.remove(el);
            break;
        }
    }
}


void World::setGravity(float gravityY)
{
    mWorld.SetGravity({0, gravityY});
    for (b2Body* b = mWorld.GetBodyList(); b; b = b->GetNext()) {
        b->SetAwake(true);
    }
}


void World::setSize(float size)
{
    shapeSize = mPPM * size;
}


void World::setActionType(int at)
{
    actiontype = at;
}


void World::createObject(b2Vec2 initpos)
{
    switch (actiontype)
    {
        case 0:
            addRect(initpos);
            break;
        case 1:
            addCirc(initpos);
            break;
        case 2:
            addFixture(initpos);
            break;
        default:
            break;
    }
}


void World::clear()
{
    for_each(begin(mDynamicShapes), end(mDynamicShapes),
             [this](decltype(*begin(mDynamicShapes)) &el)
    {
        mWorld.DestroyBody(el->getBody());
    });

    for_each(begin(mStaticShapes), end(mStaticShapes),
             [this](decltype(*begin(mStaticShapes)) &el)
    {
        mWorld.DestroyBody(el->getBody());
    });

    mDynamicShapes.clear();
    mStaticShapes.clear();
}


int World::getBodyCount()
{
    return mWorld.GetBodyCount() - static_cast<int>(mPermanentShapes.size()) - 1;
}
