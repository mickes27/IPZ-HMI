#ifndef BOOK_MANUALCONTROL_HPP
#define BOOK_MANUALCONTROL_HPP

#include "State.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <opencv2/opencv.hpp>
#include <thread>


class ManualControlState : public State
{
public:
	ManualControlState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Image camImage;
	sf::Texture camTexture;
	sf::Sprite camSprite;

	sf::Sprite mBackgroundSprite;

	sf::Text watInfo;
	sf::Text watState;

	sf::Text mesInfo;
	sf::Text mesState;

	sf::Text gearVal;
	sf::Text gearInfo;

	sf::Text currentMesInfo;
	sf::Text mesHumidityInfo;
	sf::Text mesTemperatureInfo;
	sf::Text mesInsolationInfo;
	sf::Text mesHumidityVal;
	sf::Text mesTemperatureVal;
	sf::Text mesInsolationVal;

	cv::VideoCapture cap;

	sf::Sprite arrowUp;
	sf::Sprite arrowDown;
	sf::Sprite arrowLeft;
	sf::Sprite arrowRight;

	sf::Sprite mesButton;
	sf::Sprite watButton;

	sf::Sprite Gear;

	bool isUp;
	bool isDown;
	bool isLeft;
	bool isRight;

	bool startMeasure;
	bool isWatering;

	bool Busy;
	bool duringMeasure;

	int gearValue;
};


#endif // BOOK_MANUALCONTROL_HPP