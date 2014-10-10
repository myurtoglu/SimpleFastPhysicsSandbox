#include "Game.hpp"

using std::to_string;
using std::make_shared;


Game::Game()
: mWindow(make_shared<sf::RenderWindow>(sf::VideoMode(xSize, ySize),
                                        "SimpleFastPhysicsSandbox",
                                        sf::Style::Close))
, mFont()
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
, mGameWorld(make_shared<World>(mWindow, PPM, separatorRatio, groundHeight,
                                gravity))
, mGui(mWindow, mGameWorld)
, mStatus(true)
{
    mFont.loadFromFile(resourcePath() +
                      "Fonts/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
    mBuffer.loadFromFile(resourcePath() + "Audio/pause_sound.wav");
    mPauseSound.setBuffer(mBuffer);
}


void Game::run()
{
    sf::Clock clock;
	auto timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow->isOpen())
    {
        auto elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
            mGui.update(elapsedTime);
            if (mStatus) {
                update();
            }
        }
        if (mStatus) {
            updateStatistics(elapsedTime);
        }
		render();
	}
}


void Game::processEvents()
{
    sf::Event event;
    while (mWindow->pollEvent(event))
	{
        mGui.handleEvent(event);
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
            case sf::Event::MouseButtonPressed:
                handlePlayerInput(event.mouseButton.button);
				break;
			case sf::Event::Closed:
				mWindow->close();
				break;
            default:
            break;
		}
	}
}


void Game::update()
{
    mGameWorld->step(TimePerFrame.asSeconds(), velocityIterations,
                     positionIterations);
}


void Game::render()
{
    mWindow->clear();
    mGameWorld->draw();
    mGui.draw();
    mWindow->draw(mStatisticsText);
    mWindow->display();
}


void Game::updateStatistics(sf::Time elapsedTime)
{
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
        mStatisticsText.setString("Frames / Second = " +
                                  to_string(mStatisticsNumFrames) + "\n" +
                                  "Time / Update = "
                                  +to_string(mStatisticsUpdateTime.asMicroseconds()
                                  / mStatisticsNumFrames) + "us\n"
                                  + "Number of Objects = "
                                  +to_string(mGameWorld->getBodyCount()));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Space) {
        if (isPressed) {
            pause();
        }
    }
    else if (key == sf::Keyboard::Escape) {
        if (isPressed) {
            mWindow->close();
        }
    }
}


void Game::handlePlayerInput(sf::Mouse::Button button)
{
    auto clickpos = sf::Mouse::getPosition(*mWindow);
    if (isInsideArea(mWindow->getSize().x, mWindow->getSize().y, clickpos)) {
        auto b2clickpos = ConvSfToB2Vec(clickpos, mWindow->getSize().y, PPM);

        if (button == sf::Mouse::Left) {
            mGameWorld->createObject(b2clickpos);
        }
        else if (button == sf::Mouse::Right) {
            mGameWorld->destroyObject(b2clickpos);
        }
    }
}


bool Game::isInsideArea(int xSize, int ySize, sf::Vector2i position)
{
    return (position.x < xSize * separatorRatio && position.x > 0 &&
            position.y < ySize - groundHeight && position.y > 0);
}


void Game::pause()
{
    mStatus = !mStatus;
    mPauseSound.play();
}
