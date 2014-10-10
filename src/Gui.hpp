#ifndef Gui_HPP_
#define Gui_HPP_

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>
#include "World.hpp"


class Gui
{
public:
        Gui(std::shared_ptr<sf::RenderWindow>, std::shared_ptr<World>);
   void update(sf::Time);
   void display();
   void draw();
   void handleEvent(sf::Event&);

private:
   void adjustGravity();
   void adjustSize();
   void handleResetClick();
   void selectShape();

private:
   sfg::SFGUI                        mSfgui;
   std::shared_ptr<sf::RenderWindow> mWindow;
   std::shared_ptr<World>            mWorld;
   sfg::Desktop                      mDesktop;
   sfg::Label::Ptr                   mGravityTitleLabel;
   sfg::Label::Ptr                   mGravityLabel;
   sfg::Label::Ptr                   mShapeTitleLabel;
   sfg::Label::Ptr                   mSizeTitleLabel;
   sfg::Label::Ptr                   mSizeLabel;
   sfg::Adjustment::Ptr              mGravityAdjustment;
   sfg::Adjustment::Ptr              mSizeAdjustment;
   sfg::RadioButton::Ptr             mShapeSelectionButton0;
   sfg::RadioButton::Ptr             mShapeSelectionButton1;
   sfg::RadioButton::Ptr             mShapeSelectionButton2;
};

#endif
