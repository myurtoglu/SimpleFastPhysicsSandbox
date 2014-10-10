#ifndef Game_HPP_
#define Game_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "World.hpp"
#include "ResourcePath.hpp"
#include "BoxSfmlHelpers.hpp"
#include "Gui.hpp"

#include <memory>
#include <string>


class Game : private sf::NonCopyable
{
public:
        Game();
   void run();

private:
   void processEvents();
   void update();
   void render();
   void updateStatistics(sf::Time);
   void handlePlayerInput(sf::Keyboard::Key, bool);
   void handlePlayerInput(sf::Mouse::Button);
   bool isInsideArea(int, int, sf::Vector2i);
   void pause();

private:
   const sf::Time                    TimePerFrame = sf::seconds(1.f/60.f);
   const float                       groundHeight = 50.f;
   const int                         PPM = 30;
   int                               velocityIterations = 6;
   int                               positionIterations = 2;
   const int                         xSize = 1200;
   const int                         ySize = 800;
   const float                       separatorRatio = 0.85;
   b2Vec2                            gravity = {0.f, -10.f};
   std::shared_ptr<sf::RenderWindow> mWindow;
   sf::Font                          mFont;
   sf::Text                          mStatisticsText;
   sf::Time                          mStatisticsUpdateTime;
   std::size_t                       mStatisticsNumFrames;
   std::shared_ptr<World>            mGameWorld;
   Gui                               mGui;
   bool                              mStatus;
   sf::SoundBuffer                   mBuffer;
   sf::Sound                         mPauseSound;
};


#endif
