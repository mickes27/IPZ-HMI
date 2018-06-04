#include "ConfigState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <SFML/Graphics/RenderWindow.hpp>


ConfigState::ConfigState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
	, mMaxAngleInfo()
	, mMaxAngleHigh()
	, mMaxAngleLow()
	, mMaxAngleCurrent()
	, mMinAngleInfo()
	, mMinAngleHigh()
	, mMinAngleLow()
	, mMinAngleCurrent()
	, mMidLeftInfo()
	, mMidLeftLow()
	, mMidLeftHigh()
	, mMidLeftCurrent()
	, mMidRightInfo()
	, mMidRightLow()
	, mMidRightHigh()
	, mMidRightCurrent()
	, mHighHueInfo()
	, mHighHueLow()
	, mHighHueHigh()
	, mHighHueCurrent()
	, mLowHueInfo()
	, mLowHueLow()
	, mLowHueHigh()
	, mLowHueCurrent()
	, mLowSaturationInfo()
	, mLowSaturationLow()
	, mLowSaturationHigh()
	, mLowSaturationCurrent()
	, mHighSaturationInfo()
	, mHighSaturationLow()
	, mHighSaturationHigh()
	, mHighSaturationCurrent()
	, mLowValueInfo()
	, mLowValueLow()
	, mLowValueHigh()
	, mLowValueCurrent()
	, mHighValueInfo()
	, mHighValueLow()
	, mHighValueHigh()
	, mHighValueCurrent()
	, mHoughVoterInfo()
	, mHoughVoterLow()
	, mHoughVoterHigh()
	, mHoughVoterCurrent()
	, mFillInfo()
	, mFillLow()
	, mFillHigh()
	, mFillCurrent()
	, mDestructionInfo()
	, mDestructionLow()
	, mDestructionHigh()
	, mDestructionCurrent()
	, mTimer(sf::Time::Zero)
	, gui(*context.window)
{
	context.window->setMouseCursorVisible(true);

	isConfigured = false;

	configStruct = context.imageproc->Parameters_check();

	try
	{
		tgui::Theme::Ptr theme = tgui::Theme::create("./Widgets/Green.txt");



		tgui::Label::Ptr label = theme->load("label");

		tgui::Slider::Ptr slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 230.f);
		slider->setSize(400, 20);
		slider->setMaximum(90);
		slider->setMinimum(0);
		slider->setValue(configStruct.MinAngle);
		gui.add(slider, "MinAngleSlider");

		slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 290.f);
		slider->setSize(400, 20);
		slider->setMaximum(180);
		slider->setMinimum(90);
		slider->setValue(configStruct.MaxAngle);
		gui.add(slider, "MaxAngleSlider");

		slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 350.f);
		slider->setSize(400, 20);
		slider->setMaximum(90);
		slider->setMinimum(0);
		slider->setValue(configStruct.MidLeft);
		gui.add(slider, "MidLeftSlider");

		slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 410.f);
		slider->setSize(400, 20);
		slider->setMaximum(90);
		slider->setMinimum(0);
		slider->setValue(configStruct.MidRight);
		gui.add(slider, "MidRightSlider");

		slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 470.f);
		slider->setSize(400, 20);
		slider->setMaximum(179);
		slider->setMinimum(0);
		slider->setValue(configStruct.LowHue);
		gui.add(slider, "LowHueSlider");

		slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 530.f);
		slider->setSize(400, 20);
		slider->setMaximum(179);
		slider->setMinimum(0);
		slider->setValue(configStruct.HighHue);
		gui.add(slider, "HighHueSlider");

		slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 590.f);
		slider->setSize(400, 20);
		slider->setMaximum(255);
		slider->setMinimum(0);
		slider->setValue(configStruct.LowSat);
		gui.add(slider, "LowSaturationSlider");

		slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 650.f);
		slider->setSize(400, 20);
		slider->setMaximum(255);
		slider->setMinimum(0);
		slider->setValue(configStruct.HighSat);
		gui.add(slider, "HighSaturationSlider");

		slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 710.f);
		slider->setSize(400, 20);
		slider->setMaximum(255);
		slider->setMinimum(0);
		slider->setValue(configStruct.LowVal);
		gui.add(slider, "LowValueSlider");

		slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 770.f);
		slider->setSize(400, 20);
		slider->setMaximum(255);
		slider->setMinimum(0);
		slider->setValue(configStruct.HighVal);
		gui.add(slider, "HighValueSlider");

		slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 830.f);
		slider->setSize(400, 20);
		slider->setMaximum(400);
		slider->setMinimum(0);
		slider->setValue(configStruct.HoughVot);
		gui.add(slider, "HoughVoterSlider");

		slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 890.f);
		slider->setSize(400, 20);
		slider->setMaximum(10);
		slider->setMinimum(0);
		slider->setValue(configStruct.Fill);
		gui.add(slider, "FillSlider");

		slider = theme->load("slider");
		slider->setPosition(context.window->getView().getSize().x / 8.f + 695.f, 950.f);
		slider->setSize(400, 20);
		slider->setMaximum(10);
		slider->setMinimum(0);
		slider->setValue(configStruct.Destr);
		gui.add(slider, "DestructionSlider");

		/*tgui::CheckBox::Ptr checkbox = theme->load("checkbox");
		checkbox->setPosition(420, 240);
		checkbox->setText("Ok, I got it");
		checkbox->setSize(25, 25);
		gui.add(checkbox, "CB1");

		checkbox = theme->load("checkbox");
		checkbox->setPosition(570, 240);
		checkbox->setText("No, I didn't");
		checkbox->setSize(25, 25);
		gui.add(checkbox, "CB2");*/
	}
	catch (const tgui::Exception& e)
	{
		std::cerr << "TGUI Exception: " << e.what() << std::endl;
		system("PAUSE");
		exit(1);
	}

	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	//******** MASA INFORMACYJ ********//

	//--- Info
	mText.setFont(context.fonts->get(Fonts::Main));
	mText.setOutlineThickness(2);
	mText.setString(L"Konfiguracja pojazdu");
	mText.setCharacterSize(60);
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize().x / 2.f, 60.f);

	//--- Minimalny k¹t
	mMinAngleInfo.setFont(context.fonts->get(Fonts::Main));
	mMinAngleInfo.setOutlineThickness(2);
	mMinAngleInfo.setString(L"Minimum angle:");
	mMinAngleInfo.setCharacterSize(60);
	mMinAngleInfo.setPosition(context.window->getView().getSize().x / 8.f, 200.f);

	mMinAngleLow.setFont(context.fonts->get(Fonts::Main));
	mMinAngleLow.setOutlineThickness(2);
	mMinAngleLow.setString(L"0");
	mMinAngleLow.setCharacterSize(30);
	mMinAngleLow.setFillColor(sf::Color(128, 128, 128));
	mMinAngleLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f , 220.f);

	mMinAngleHigh.setFont(context.fonts->get(Fonts::Main));
	mMinAngleHigh.setOutlineThickness(2);
	mMinAngleHigh.setString(L"90");
	mMinAngleHigh.setCharacterSize(30);
	mMinAngleHigh.setFillColor(sf::Color(128, 128, 128));
	mMinAngleHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 220.f);

	mMinAngleCurrent.setFont(context.fonts->get(Fonts::Main));
	mMinAngleCurrent.setOutlineThickness(2);
	mMinAngleCurrent.setString(toString(configStruct.MinAngle));
	mMinAngleCurrent.setCharacterSize(60);
	mMinAngleCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 200.f);

	//--- Maksymalny k¹t
	mMaxAngleInfo.setFont(context.fonts->get(Fonts::Main));
	mMaxAngleInfo.setOutlineThickness(2);
	mMaxAngleInfo.setString(L"Maximum angle:");
	mMaxAngleInfo.setCharacterSize(60);
	mMaxAngleInfo.setPosition(context.window->getView().getSize().x / 8.f, 260.f);

	mMaxAngleLow.setFont(context.fonts->get(Fonts::Main));
	mMaxAngleLow.setOutlineThickness(2);
	mMaxAngleLow.setString(L"90");
	mMaxAngleLow.setCharacterSize(30);
	mMaxAngleLow.setFillColor(sf::Color(128, 128, 128));
	mMaxAngleLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f, 280.f);

	mMaxAngleHigh.setFont(context.fonts->get(Fonts::Main));
	mMaxAngleHigh.setOutlineThickness(2);
	mMaxAngleHigh.setString(L"180");
	mMaxAngleHigh.setCharacterSize(30);
	mMaxAngleHigh.setFillColor(sf::Color(128, 128, 128));
	mMaxAngleHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 280.f);

	mMaxAngleCurrent.setFont(context.fonts->get(Fonts::Main));
	mMaxAngleCurrent.setOutlineThickness(2);
	mMaxAngleCurrent.setString(toString(configStruct.MaxAngle));
	mMaxAngleCurrent.setCharacterSize(60);
	mMaxAngleCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 260.f);

	//--- Mid left
	mMidLeftInfo.setFont(context.fonts->get(Fonts::Main));
	mMidLeftInfo.setOutlineThickness(2);
	mMidLeftInfo.setString(L"Mid left:");
	mMidLeftInfo.setCharacterSize(60);
	mMidLeftInfo.setPosition(context.window->getView().getSize().x / 8.f, 320.f);

	mMidLeftLow.setFont(context.fonts->get(Fonts::Main));
	mMidLeftLow.setOutlineThickness(2);
	mMidLeftLow.setString(L"0");
	mMidLeftLow.setCharacterSize(30);
	mMidLeftLow.setFillColor(sf::Color(128, 128, 128));
	mMidLeftLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f, 340.f);

	mMidLeftHigh.setFont(context.fonts->get(Fonts::Main));
	mMidLeftHigh.setOutlineThickness(2);
	mMidLeftHigh.setString(L"90");
	mMidLeftHigh.setCharacterSize(30);
	mMidLeftHigh.setFillColor(sf::Color(128, 128, 128));
	mMidLeftHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 340.f);

	mMidLeftCurrent.setFont(context.fonts->get(Fonts::Main));
	mMidLeftCurrent.setOutlineThickness(2);
	mMidLeftCurrent.setString(toString(configStruct.MidLeft));
	mMidLeftCurrent.setCharacterSize(60);
	mMidLeftCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 320.f);

	//--- Mid right
	mMidRightInfo.setFont(context.fonts->get(Fonts::Main));
	mMidRightInfo.setOutlineThickness(2);
	mMidRightInfo.setString(L"Mid right:");
	mMidRightInfo.setCharacterSize(60);
	mMidRightInfo.setPosition(context.window->getView().getSize().x / 8.f, 380.f);

	mMidRightLow.setFont(context.fonts->get(Fonts::Main));
	mMidRightLow.setOutlineThickness(2);
	mMidRightLow.setString(L"0");
	mMidRightLow.setCharacterSize(30);
	mMidRightLow.setFillColor(sf::Color(128, 128, 128));
	mMidRightLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f, 400.f);

	mMidRightHigh.setFont(context.fonts->get(Fonts::Main));
	mMidRightHigh.setOutlineThickness(2);
	mMidRightHigh.setString(L"90");
	mMidRightHigh.setCharacterSize(30);
	mMidRightHigh.setFillColor(sf::Color(128, 128, 128));
	mMidRightHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 400.f);

	mMidRightCurrent.setFont(context.fonts->get(Fonts::Main));
	mMidRightCurrent.setOutlineThickness(2);
	mMidRightCurrent.setString(toString(configStruct.MidRight));
	mMidRightCurrent.setCharacterSize(60);
	mMidRightCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 380.f);

	//--- Low Hue
	mLowHueInfo.setFont(context.fonts->get(Fonts::Main));
	mLowHueInfo.setOutlineThickness(2);
	mLowHueInfo.setString(L"Low Hue:");
	mLowHueInfo.setCharacterSize(60);
	mLowHueInfo.setPosition(context.window->getView().getSize().x / 8.f, 440.f);

	mLowHueLow.setFont(context.fonts->get(Fonts::Main));
	mLowHueLow.setOutlineThickness(2);
	mLowHueLow.setString(L"0");
	mLowHueLow.setCharacterSize(30);
	mLowHueLow.setFillColor(sf::Color(128, 128, 128));
	mLowHueLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f, 460.f);

	mLowHueHigh.setFont(context.fonts->get(Fonts::Main));
	mLowHueHigh.setOutlineThickness(2);
	mLowHueHigh.setString(L"179");
	mLowHueHigh.setCharacterSize(30);
	mLowHueHigh.setFillColor(sf::Color(128, 128, 128));
	mLowHueHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 460.f);

	mLowHueCurrent.setFont(context.fonts->get(Fonts::Main));
	mLowHueCurrent.setOutlineThickness(2);
	mLowHueCurrent.setString(toString(configStruct.LowHue));
	mLowHueCurrent.setCharacterSize(60);
	mLowHueCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 440.f);

	//--- High Hue
	mHighHueInfo.setFont(context.fonts->get(Fonts::Main));
	mHighHueInfo.setOutlineThickness(2);
	mHighHueInfo.setString(L"High Hue:");
	mHighHueInfo.setCharacterSize(60);
	mHighHueInfo.setPosition(context.window->getView().getSize().x / 8.f, 500.f);

	mHighHueLow.setFont(context.fonts->get(Fonts::Main));
	mHighHueLow.setOutlineThickness(2);
	mHighHueLow.setString(L"0");
	mHighHueLow.setCharacterSize(30);
	mHighHueLow.setFillColor(sf::Color(128, 128, 128));
	mHighHueLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f, 520.f);

	mHighHueHigh.setFont(context.fonts->get(Fonts::Main));
	mHighHueHigh.setOutlineThickness(2);
	mHighHueHigh.setString(L"179");
	mHighHueHigh.setCharacterSize(30);
	mHighHueHigh.setFillColor(sf::Color(128, 128, 128));
	mHighHueHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 520.f);

	mHighHueCurrent.setFont(context.fonts->get(Fonts::Main));
	mHighHueCurrent.setOutlineThickness(2);
	mHighHueCurrent.setString(toString(configStruct.HighHue));
	mHighHueCurrent.setCharacterSize(60);
	mHighHueCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 500.f);

	//--- Low Saturation
	mLowSaturationInfo.setFont(context.fonts->get(Fonts::Main));
	mLowSaturationInfo.setOutlineThickness(2);
	mLowSaturationInfo.setString(L"Low Saturation:");
	mLowSaturationInfo.setCharacterSize(60);
	mLowSaturationInfo.setPosition(context.window->getView().getSize().x / 8.f, 560.f);

	mLowSaturationLow.setFont(context.fonts->get(Fonts::Main));
	mLowSaturationLow.setOutlineThickness(2);
	mLowSaturationLow.setString(L"0");
	mLowSaturationLow.setCharacterSize(30);
	mLowSaturationLow.setFillColor(sf::Color(128, 128, 128));
	mLowSaturationLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f, 580.f);

	mLowSaturationHigh.setFont(context.fonts->get(Fonts::Main));
	mLowSaturationHigh.setOutlineThickness(2);
	mLowSaturationHigh.setString(L"255");
	mLowSaturationHigh.setCharacterSize(30);
	mLowSaturationHigh.setFillColor(sf::Color(128, 128, 128));
	mLowSaturationHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 580.f);

	mLowSaturationCurrent.setFont(context.fonts->get(Fonts::Main));
	mLowSaturationCurrent.setOutlineThickness(2);
	mLowSaturationCurrent.setString(toString(configStruct.LowSat));
	mLowSaturationCurrent.setCharacterSize(60);
	mLowSaturationCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 560.f);

	//--- High Saturation
	mHighSaturationInfo.setFont(context.fonts->get(Fonts::Main));
	mHighSaturationInfo.setOutlineThickness(2);
	mHighSaturationInfo.setString(L"High Saturation:");
	mHighSaturationInfo.setCharacterSize(60);
	mHighSaturationInfo.setPosition(context.window->getView().getSize().x / 8.f, 620.f);

	mHighSaturationLow.setFont(context.fonts->get(Fonts::Main));
	mHighSaturationLow.setOutlineThickness(2);
	mHighSaturationLow.setString(L"0");
	mHighSaturationLow.setCharacterSize(30);
	mHighSaturationLow.setFillColor(sf::Color(128, 128, 128));
	mHighSaturationLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f, 640.f);

	mHighSaturationHigh.setFont(context.fonts->get(Fonts::Main));
	mHighSaturationHigh.setOutlineThickness(2);
	mHighSaturationHigh.setString(L"255");
	mHighSaturationHigh.setCharacterSize(30);
	mHighSaturationHigh.setFillColor(sf::Color(128, 128, 128));
	mHighSaturationHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 640.f);

	mHighSaturationCurrent.setFont(context.fonts->get(Fonts::Main));
	mHighSaturationCurrent.setOutlineThickness(2);
	mHighSaturationCurrent.setString(toString(configStruct.HighSat));
	mHighSaturationCurrent.setCharacterSize(60);
	mHighSaturationCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 620.f);

	//--- Low Value
	mLowValueInfo.setFont(context.fonts->get(Fonts::Main));
	mLowValueInfo.setOutlineThickness(2);
	mLowValueInfo.setString(L"Low Value:");
	mLowValueInfo.setCharacterSize(60);
	mLowValueInfo.setPosition(context.window->getView().getSize().x / 8.f, 680.f);

	mLowValueLow.setFont(context.fonts->get(Fonts::Main));
	mLowValueLow.setOutlineThickness(2);
	mLowValueLow.setString(L"0");
	mLowValueLow.setCharacterSize(30);
	mLowValueLow.setFillColor(sf::Color(128, 128, 128));
	mLowValueLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f, 700.f);

	mLowValueHigh.setFont(context.fonts->get(Fonts::Main));
	mLowValueHigh.setOutlineThickness(2);
	mLowValueHigh.setString(L"255");
	mLowValueHigh.setCharacterSize(30);
	mLowValueHigh.setFillColor(sf::Color(128, 128, 128));
	mLowValueHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 700.f);

	mLowValueCurrent.setFont(context.fonts->get(Fonts::Main));
	mLowValueCurrent.setOutlineThickness(2);
	mLowValueCurrent.setString(toString(configStruct.LowVal));
	mLowValueCurrent.setCharacterSize(60);
	mLowValueCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 680.f);

	//--- High Value
	mHighValueInfo.setFont(context.fonts->get(Fonts::Main));
	mHighValueInfo.setOutlineThickness(2);
	mHighValueInfo.setString(L"High Value:");
	mHighValueInfo.setCharacterSize(60);
	mHighValueInfo.setPosition(context.window->getView().getSize().x / 8.f, 740.f);

	mHighValueLow.setFont(context.fonts->get(Fonts::Main));
	mHighValueLow.setOutlineThickness(2);
	mHighValueLow.setString(L"0");
	mHighValueLow.setCharacterSize(30);
	mHighValueLow.setFillColor(sf::Color(128, 128, 128));
	mHighValueLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f, 760.f);

	mHighValueHigh.setFont(context.fonts->get(Fonts::Main));
	mHighValueHigh.setOutlineThickness(2);
	mHighValueHigh.setString(L"255");
	mHighValueHigh.setCharacterSize(30);
	mHighValueHigh.setFillColor(sf::Color(128, 128, 128));
	mHighValueHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 760.f);

	mHighValueCurrent.setFont(context.fonts->get(Fonts::Main));
	mHighValueCurrent.setOutlineThickness(2);
	mHighValueCurrent.setString(toString(configStruct.HighVal));
	mHighValueCurrent.setCharacterSize(60);
	mHighValueCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 740.f);

	//--- Hough Voter
	mHoughVoterInfo.setFont(context.fonts->get(Fonts::Main));
	mHoughVoterInfo.setOutlineThickness(2);
	mHoughVoterInfo.setString(L"Hough Voter:");
	mHoughVoterInfo.setCharacterSize(60);
	mHoughVoterInfo.setPosition(context.window->getView().getSize().x / 8.f, 800.f);

	mHoughVoterLow.setFont(context.fonts->get(Fonts::Main));
	mHoughVoterLow.setOutlineThickness(2);
	mHoughVoterLow.setString(L"0");
	mHoughVoterLow.setCharacterSize(30);
	mHoughVoterLow.setFillColor(sf::Color(128, 128, 128));
	mHoughVoterLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f, 820.f);

	mHoughVoterHigh.setFont(context.fonts->get(Fonts::Main));
	mHoughVoterHigh.setOutlineThickness(2);
	mHoughVoterHigh.setString(L"400");
	mHoughVoterHigh.setCharacterSize(30);
	mHoughVoterHigh.setFillColor(sf::Color(128, 128, 128));
	mHoughVoterHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 820.f);

	mHoughVoterCurrent.setFont(context.fonts->get(Fonts::Main));
	mHoughVoterCurrent.setOutlineThickness(2);
	mHoughVoterCurrent.setString(toString(configStruct.HoughVot));
	mHoughVoterCurrent.setCharacterSize(60);
	mHoughVoterCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 800.f);

	//--- Fill
	mFillInfo.setFont(context.fonts->get(Fonts::Main));
	mFillInfo.setOutlineThickness(2);
	mFillInfo.setString(L"Fill:");
	mFillInfo.setCharacterSize(60);
	mFillInfo.setPosition(context.window->getView().getSize().x / 8.f, 860.f);

	mFillLow.setFont(context.fonts->get(Fonts::Main));
	mFillLow.setOutlineThickness(2);
	mFillLow.setString(L"0");
	mFillLow.setCharacterSize(30);
	mFillLow.setFillColor(sf::Color(128, 128, 128));
	mFillLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f, 880.f);

	mFillHigh.setFont(context.fonts->get(Fonts::Main));
	mFillHigh.setOutlineThickness(2);
	mFillHigh.setString(L"10");
	mFillHigh.setCharacterSize(30);
	mFillHigh.setFillColor(sf::Color(128, 128, 128));
	mFillHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 880.f);

	mFillCurrent.setFont(context.fonts->get(Fonts::Main));
	mFillCurrent.setOutlineThickness(2);
	mFillCurrent.setString(toString(configStruct.Fill));
	mFillCurrent.setCharacterSize(60);
	mFillCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 860.f);

	//--- Destruction
	mDestructionInfo.setFont(context.fonts->get(Fonts::Main));
	mDestructionInfo.setOutlineThickness(2);
	mDestructionInfo.setString(L"Destruction:");
	mDestructionInfo.setCharacterSize(60);
	mDestructionInfo.setPosition(context.window->getView().getSize().x / 8.f, 920.f);

	mDestructionLow.setFont(context.fonts->get(Fonts::Main));
	mDestructionLow.setOutlineThickness(2);
	mDestructionLow.setString(L"0");
	mDestructionLow.setCharacterSize(30);
	mDestructionLow.setFillColor(sf::Color(128, 128, 128));
	mDestructionLow.setPosition(context.window->getView().getSize().x / 8.f + 650.f, 940.f);

	mDestructionHigh.setFont(context.fonts->get(Fonts::Main));
	mDestructionHigh.setOutlineThickness(2);
	mDestructionHigh.setString(L"10");
	mDestructionHigh.setCharacterSize(30);
	mDestructionHigh.setFillColor(sf::Color(128, 128, 128));
	mDestructionHigh.setPosition(context.window->getView().getSize().x / 8.f + 1120.f, 940.f);

	mDestructionCurrent.setFont(context.fonts->get(Fonts::Main));
	mDestructionCurrent.setOutlineThickness(2);
	mDestructionCurrent.setString(toString(configStruct.Destr));
	mDestructionCurrent.setCharacterSize(60);
	mDestructionCurrent.setPosition(context.window->getView().getSize().x / 8.f + 1200.f, 920.f);
}

void ConfigState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);
	window.draw(mText);

	window.draw(mMinAngleInfo);
	window.draw(mMinAngleLow);
	window.draw(mMinAngleHigh);
	window.draw(mMinAngleCurrent);

	window.draw(mMaxAngleInfo);
	window.draw(mMaxAngleLow);
	window.draw(mMaxAngleHigh);
	window.draw(mMaxAngleCurrent);

	window.draw(mMidLeftInfo);
	window.draw(mMidLeftLow);
	window.draw(mMidLeftHigh);
	window.draw(mMidLeftCurrent);

	window.draw(mMidRightInfo);
	window.draw(mMidRightLow);
	window.draw(mMidRightHigh);
	window.draw(mMidRightCurrent);

	window.draw(mLowHueInfo);
	window.draw(mLowHueLow);
	window.draw(mLowHueHigh);
	window.draw(mLowHueCurrent);

	window.draw(mHighHueInfo);
	window.draw(mHighHueLow);
	window.draw(mHighHueHigh);
	window.draw(mHighHueCurrent);

	window.draw(mLowSaturationInfo);
	window.draw(mLowSaturationLow);
	window.draw(mLowSaturationHigh);
	window.draw(mLowSaturationCurrent);

	window.draw(mHighSaturationInfo);
	window.draw(mHighSaturationLow);
	window.draw(mHighSaturationHigh);
	window.draw(mHighSaturationCurrent);

	window.draw(mLowValueInfo);
	window.draw(mLowValueLow);
	window.draw(mLowValueHigh);
	window.draw(mLowValueCurrent);

	window.draw(mHighValueInfo);
	window.draw(mHighValueLow);
	window.draw(mHighValueHigh);
	window.draw(mHighValueCurrent);

	window.draw(mHoughVoterInfo);
	window.draw(mHoughVoterLow);
	window.draw(mHoughVoterHigh);
	window.draw(mHoughVoterCurrent);

	window.draw(mFillInfo);
	window.draw(mFillLow);
	window.draw(mFillHigh);
	window.draw(mFillCurrent);

	window.draw(mDestructionInfo);
	window.draw(mDestructionLow);
	window.draw(mDestructionHigh);
	window.draw(mDestructionCurrent);

	gui.draw();
}

bool ConfigState::update(sf::Time dt)
{
	tgui::Slider::Ptr minAngleSlider = gui.get<tgui::Slider>("MinAngleSlider");
	mMinAngleCurrent.setString(toString(minAngleSlider->getValue()));

	tgui::Slider::Ptr maxAngleSlider = gui.get<tgui::Slider>("MaxAngleSlider");
	mMaxAngleCurrent.setString(toString(maxAngleSlider->getValue()));

	tgui::Slider::Ptr midLeftSlider = gui.get<tgui::Slider>("MidLeftSlider");
	mMidLeftCurrent.setString(toString(midLeftSlider->getValue()));

	tgui::Slider::Ptr midRightSlider = gui.get<tgui::Slider>("MidRightSlider");
	mMidRightCurrent.setString(toString(midRightSlider->getValue()));

	tgui::Slider::Ptr lowHueSlider = gui.get<tgui::Slider>("LowHueSlider");
	mLowHueCurrent.setString(toString(lowHueSlider->getValue()));

	tgui::Slider::Ptr highHueSlider = gui.get<tgui::Slider>("HighHueSlider");
	mHighHueCurrent.setString(toString(highHueSlider->getValue()));

	tgui::Slider::Ptr lowSaturationSlider = gui.get<tgui::Slider>("LowSaturationSlider");
	mLowSaturationCurrent.setString(toString(lowSaturationSlider->getValue()));

	tgui::Slider::Ptr highSaturationSlider = gui.get<tgui::Slider>("HighSaturationSlider");
	mHighSaturationCurrent.setString(toString(highSaturationSlider->getValue()));

	tgui::Slider::Ptr lowValueSlider = gui.get<tgui::Slider>("LowValueSlider");
	mLowValueCurrent.setString(toString(lowValueSlider->getValue()));

	tgui::Slider::Ptr highValueSlider = gui.get<tgui::Slider>("HighValueSlider");
	mHighValueCurrent.setString(toString(highValueSlider->getValue()));

	tgui::Slider::Ptr houghVoterSlider = gui.get<tgui::Slider>("HoughVoterSlider");
	mHoughVoterCurrent.setString(toString(houghVoterSlider->getValue()));

	tgui::Slider::Ptr fillSlider = gui.get<tgui::Slider>("FillSlider");
	mFillCurrent.setString(toString(fillSlider->getValue()));

	tgui::Slider::Ptr destructionSlider = gui.get<tgui::Slider>("DestructionSlider");
	mDestructionCurrent.setString(toString(destructionSlider->getValue()));

	if (isConfigured) {
		mTimer += dt;

		if (mTimer >= sf::seconds(1.0f))
		{
			requestStackPop();
			requestStackPush(States::Menu);
		}
	}

	return true;
}

bool ConfigState::handleEvent(const sf::Event& event)
{
	gui.handleEvent(event);

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			requestStackPop();
			requestStackPush(States::Menu);
		}
		else if (event.key.code == sf::Keyboard::Enter) {
			tgui::Slider::Ptr minAngle = gui.get<tgui::Slider>("MinAngleSlider");
			tgui::Slider::Ptr maxAngle = gui.get<tgui::Slider>("MaxAngleSlider");
			tgui::Slider::Ptr midLeft = gui.get<tgui::Slider>("MidLeftSlider");
			tgui::Slider::Ptr midRight = gui.get<tgui::Slider>("MidRightSlider");
			tgui::Slider::Ptr lowHue = gui.get<tgui::Slider>("LowHueSlider");
			tgui::Slider::Ptr highHue = gui.get<tgui::Slider>("HighHueSlider");
			tgui::Slider::Ptr lowSat = gui.get<tgui::Slider>("LowSaturationSlider");
			tgui::Slider::Ptr highSat = gui.get<tgui::Slider>("HighSaturationSlider");
			tgui::Slider::Ptr lowVal = gui.get<tgui::Slider>("LowValueSlider");
			tgui::Slider::Ptr highVal = gui.get<tgui::Slider>("HighValueSlider");
			tgui::Slider::Ptr houghVoter = gui.get<tgui::Slider>("HoughVoterSlider");
			tgui::Slider::Ptr Fill = gui.get<tgui::Slider>("FillSlider");
			tgui::Slider::Ptr Destr = gui.get<tgui::Slider>("DestructionSlider");


			collectData(minAngle, maxAngle, midLeft, midRight, lowHue, highHue, lowSat, highSat, lowVal, highVal, houghVoter, Fill, Destr);
			isConfigured = true;
		}
	}

	return true;
}

void ConfigState::collectData(tgui::Slider::Ptr maxAngle, tgui::Slider::Ptr minAngle, tgui::Slider::Ptr midLeft, tgui::Slider::Ptr midRight, tgui::Slider::Ptr lowHue, tgui::Slider::Ptr highHue, tgui::Slider::Ptr lowSat, tgui::Slider::Ptr highSat, tgui::Slider::Ptr lowVal, tgui::Slider::Ptr highVal, tgui::Slider::Ptr houghVoter, tgui::Slider::Ptr Fill, tgui::Slider::Ptr Destr)
{
	configStruct.MinAngle = minAngle->getValue();
	configStruct.MaxAngle = maxAngle->getValue();
	configStruct.MidLeft = midLeft->getValue();
	configStruct.MidRight = midRight->getValue();
	configStruct.LowHue = lowHue->getValue();
	configStruct.HighHue = highHue->getValue();
	configStruct.LowSat = lowSat->getValue();
	configStruct.HighSat = highSat->getValue();
	configStruct.LowVal = lowVal->getValue();
	configStruct.HighVal = highVal->getValue();
	configStruct.HoughVot = houghVoter->getValue();
	configStruct.Fill = Fill->getValue();
	configStruct.Destr = Destr->getValue();

	getContext().imageproc->Parameters_load(configStruct);

}