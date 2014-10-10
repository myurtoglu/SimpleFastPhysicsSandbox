#include "Gui.hpp"

using std::shared_ptr;
using std::bind;
using std::stringstream;


Gui::Gui(shared_ptr<sf::RenderWindow> window, shared_ptr<World> world)
: mSfgui()
, mWindow(window)
, mWorld(world)
, mDesktop()
{
    auto mButton = sfg::Button::Create("Reset Sandbox");
    mButton->GetSignal(sfg::Widget::OnLeftClick).Connect(bind(&Gui::handleResetClick,
                                                              this));
    auto mBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);

    mGravityLabel = sfg::Label::Create("10 (m/s^2)");
    mGravityTitleLabel = sfg::Label::Create("Gravity: ");
    mShapeTitleLabel = sfg::Label::Create("Shape selection: ");
    mSizeTitleLabel = sfg::Label::Create("Size: ");
    mSizeLabel = sfg::Label::Create("1 (m)");

    auto gravityScrollbar = sfg::Scrollbar::Create(sfg::Scrollbar::Orientation::HORIZONTAL);
    mGravityAdjustment = gravityScrollbar->GetAdjustment();
    mGravityAdjustment->SetLower(-10.f);
    mGravityAdjustment->SetUpper(20.f);
    mGravityAdjustment->SetValue(10.f);
    mGravityAdjustment->SetMinorStep(1.f);
    mGravityAdjustment->SetMajorStep(5.f);
    mGravityAdjustment->GetSignal(sfg::Adjustment::OnChange).Connect(bind(&Gui::adjustGravity,
                                                                          this));
    mShapeSelectionButton0 = sfg::RadioButton::Create("Square");
	mShapeSelectionButton1 = sfg::RadioButton::Create("Disk",
                                                      mShapeSelectionButton0->GetGroup());
    mShapeSelectionButton2 = sfg::RadioButton::Create("Fixture",
                                                      mShapeSelectionButton0->GetGroup());
    mShapeSelectionButton0->SetActive(true);
    mShapeSelectionButton0->GetSignal(sfg::ToggleButton::OnToggle).Connect(bind(&Gui::selectShape, this));
	mShapeSelectionButton1->GetSignal(sfg::ToggleButton::OnToggle).Connect(bind(&Gui::selectShape, this));
	mShapeSelectionButton2->GetSignal(sfg::ToggleButton::OnToggle).Connect(bind(&Gui::selectShape, this));


    // Size scrollbar
    auto sizeScrollbar = sfg::Scrollbar::Create(sfg::Scrollbar::Orientation::HORIZONTAL);
    mSizeAdjustment = sizeScrollbar->GetAdjustment();
    mSizeAdjustment->SetLower(0.1f);
	mSizeAdjustment->SetUpper(10.f);
    mSizeAdjustment->SetValue(1.f);
    mSizeAdjustment->SetMinorStep(0.1f);
    mSizeAdjustment->SetMajorStep(1.f);
    mSizeAdjustment->GetSignal(sfg::Adjustment::OnChange).Connect(bind(&Gui::adjustSize,
                                                                       this));
    mBox->Pack(mGravityTitleLabel);
    mBox->Pack(gravityScrollbar);
    mBox->Pack(mGravityLabel);
    mBox->Pack(sfg::Separator::Create());
    mBox->Pack(mShapeTitleLabel);
    mBox->Pack(mShapeSelectionButton0);
    mBox->Pack(mShapeSelectionButton1);
    mBox->Pack(mShapeSelectionButton2);
    mBox->Pack(sfg::Separator::Create());
    mBox->Pack(mSizeTitleLabel);
    mBox->Pack(sizeScrollbar);
    mBox->Pack(mSizeLabel);
    mBox->Pack(sfg::Separator::Create());
    mBox->Pack(mButton, false);

    auto mSfgwindow = sfg::Window::Create();
    mSfgwindow->SetTitle("Settings");
    mSfgwindow->SetPosition({static_cast<float>(0.86*window->getSize().x), 10});
    mSfgwindow->Add(mBox);
    mDesktop.Add(mSfgwindow);
}


void Gui::update(sf::Time elapsedTime)
{
    mDesktop.Update(elapsedTime.asSeconds());
}


void Gui::draw()
{
    mSfgui.Display(*mWindow);
}


void Gui::handleEvent(sf::Event &event)
{
    mDesktop.HandleEvent(event);
}


void Gui::adjustGravity()
{
    stringstream sstr;
	sstr << mGravityAdjustment->GetValue();
	mGravityLabel->SetText(sstr.str() + " (m/s^2)");
    mWorld->setGravity(-atof(sstr.str().c_str()));
}


void Gui::adjustSize()
{
    stringstream sstr;
	sstr << mSizeAdjustment->GetValue();
	mSizeLabel->SetText(sstr.str() + " (m)");
    mWorld->setSize(atof(sstr.str().c_str()));
}


void Gui::handleResetClick()
{
    mGravityAdjustment->SetValue(10.f);
    mSizeAdjustment->SetValue(1.f);
    mShapeSelectionButton0->SetActive(true);
    mWorld->clear();
}


void Gui::selectShape()
{
    if(mShapeSelectionButton0->IsActive()) {
        mWorld->setActionType(0);
	}
	else if(mShapeSelectionButton1->IsActive()) {
        mWorld->setActionType(1);
	}
	else if(mShapeSelectionButton2->IsActive()) {
        mWorld->setActionType(2);
	}
}
