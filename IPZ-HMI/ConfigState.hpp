#ifndef BOOK_CONFIGSTATE_HPP
#define BOOK_CONFIGSTATE_HPP

#include "State.hpp"
#include "Structs.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <TGUI\TGUI.hpp>


class ConfigState : public State
{
public:
	ConfigState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mText;

	sf::Text			mMaxAngleInfo;
	sf::Text			mMaxAngleLow;
	sf::Text			mMaxAngleHigh;
	sf::Text			mMaxAngleCurrent;

	sf::Text			mMinAngleInfo;
	sf::Text			mMinAngleLow;
	sf::Text			mMinAngleHigh;
	sf::Text			mMinAngleCurrent;

	sf::Text			mMidLeftInfo;
	sf::Text			mMidLeftLow;
	sf::Text			mMidLeftHigh;
	sf::Text			mMidLeftCurrent;

	sf::Text			mMidRightInfo;
	sf::Text			mMidRightLow;
	sf::Text			mMidRightHigh;
	sf::Text			mMidRightCurrent;

	sf::Text			mHighHueInfo;
	sf::Text			mHighHueLow;
	sf::Text			mHighHueHigh;
	sf::Text			mHighHueCurrent;

	sf::Text			mLowHueInfo;
	sf::Text			mLowHueLow;
	sf::Text			mLowHueHigh;
	sf::Text			mLowHueCurrent;

	sf::Text			mLowSaturationInfo;
	sf::Text			mLowSaturationLow;
	sf::Text			mLowSaturationHigh;
	sf::Text			mLowSaturationCurrent;

	sf::Text			mHighSaturationInfo;
	sf::Text			mHighSaturationLow;
	sf::Text			mHighSaturationHigh;
	sf::Text			mHighSaturationCurrent;

	sf::Text			mLowValueInfo;
	sf::Text			mLowValueLow;
	sf::Text			mLowValueHigh;
	sf::Text			mLowValueCurrent;

	sf::Text			mHighValueInfo;
	sf::Text			mHighValueLow;
	sf::Text			mHighValueHigh;
	sf::Text			mHighValueCurrent;

	sf::Text			mHoughVoterInfo;
	sf::Text			mHoughVoterLow;
	sf::Text			mHoughVoterHigh;
	sf::Text			mHoughVoterCurrent;

	sf::Text			mFillInfo;
	sf::Text			mFillLow;
	sf::Text			mFillHigh;
	sf::Text			mFillCurrent;

	sf::Text			mDestructionInfo;
	sf::Text			mDestructionLow;
	sf::Text			mDestructionHigh;
	sf::Text			mDestructionCurrent;

	tgui::Gui           gui;

	Config				configStruct;
	void				collectData(tgui::Slider::Ptr maxAngle, tgui::Slider::Ptr minAngle, tgui::Slider::Ptr midLeft, tgui::Slider::Ptr midRight, tgui::Slider::Ptr lowHue, tgui::Slider::Ptr highHue, tgui::Slider::Ptr lowSat, tgui::Slider::Ptr highSat, tgui::Slider::Ptr lowVal, tgui::Slider::Ptr highVal, tgui::Slider::Ptr houghVoter, tgui::Slider::Ptr Fill, tgui::Slider::Ptr Destr);

	sf::Time			mTimer;
	bool				isConfigured;
};

#endif // BOOK_CONFIGSTATE_HPP
