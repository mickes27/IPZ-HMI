#include "ManualControlState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include <iostream>
#include "Przetwarzanie_obrazu.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


ManualControlState::ManualControlState(StateStack& stack, Context context)
	: State(stack, context)
	, cap(0)
	, isUp(false)
	, isDown(false)
	, isLeft(false)
	, isRight(false)
	, isMeasuring(false)
	, isWatering(false)
{

	if (!cap.isOpened()) {
		exit(-1);
	}

	sf::Texture& texture = context.textures->get(Textures::ManualControl);
	sf::Texture& arrow = context.textures->get(Textures::Arrow);
	sf::Texture& button = context.textures->get(Textures::ButtonGreen);

	sf::Font& font = context.fonts->get(Fonts::Main);


	mBackgroundSprite.setTexture(texture);

	//--- Arrows
	arrowUp.setTexture(arrow);
	centerOrigin(arrowUp);
	arrowUp.setPosition(960.f, 650.f);
	arrowUp.rotate(-90);

	arrowDown.setTexture(arrow);
	centerOrigin(arrowDown);
	arrowDown.setPosition(960.f, 970.f);
	arrowDown.rotate(90);

	arrowLeft.setTexture(arrow);
	centerOrigin(arrowLeft);
	arrowLeft.setPosition(800.f, 810.f);
	arrowLeft.rotate(180);

	arrowRight.setTexture(arrow);
	centerOrigin(arrowRight);
	arrowRight.setPosition(1120.f, 810.f);

	//---Buttons
	mesButton.setTexture(button);
	centerOrigin(mesButton);
	mesButton.setPosition(1600.f, 810.f);

	watButton.setTexture(button);
	centerOrigin(watButton);
	watButton.setPosition(320.f, 810.f);
	
	// A simple menu demonstration

	watInfo.setFont(font);
	watInfo.setString(L"[Q]");
	watInfo.setCharacterSize(60);
	watInfo.setOutlineThickness(2);
	centerOrigin(watInfo);
	watInfo.setPosition(320.f, 940.f);

	watState.setFont(font);
	watState.setString(L"Podlewanie");
	watState.setCharacterSize(60);
	watState.setOutlineThickness(2);
	centerOrigin(watState);
	watState.setPosition(320.f, 670.f);

	mesInfo.setFont(font);
	mesInfo.setString(L"[E]");
	mesInfo.setCharacterSize(60);
	mesInfo.setOutlineThickness(2);
	centerOrigin(mesInfo);
	mesInfo.setPosition(1600.f, 940.f);

	mesState.setFont(font);
	mesState.setString(L"Pomiar");
	mesState.setCharacterSize(60);
	mesState.setOutlineThickness(2);
	centerOrigin(mesState);
	mesState.setPosition(1600.f, 670.f);

}


void ManualControlState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	window.draw(arrowUp);
	window.draw(arrowDown);
	window.draw(arrowLeft);
	window.draw(arrowRight);

	window.draw(mesButton);
	window.draw(watButton);

	centerOrigin(watInfo);
	window.draw(watInfo);
	centerOrigin(watState);
	window.draw(watState);

	centerOrigin(mesInfo);
	window.draw(mesInfo);
	centerOrigin(mesState);
	window.draw(mesState);


	//--- Przechwytywanie okna OpenCV
	cv::Mat frameRGB, frameRGBA;

	cap >> frameRGB;

	if (frameRGB.empty())
	{
		std::cout << "Walnal obraz" << std::endl;
		system("PAUSE");
		return;
	}

	cv::cvtColor(frameRGB, frameRGBA, cv::COLOR_BGR2RGBA);

	camImage.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());

	if (!camTexture.loadFromImage(camImage))
	{
		std::cout << "Brak obrazu" << std::endl;
		return;
	}

	camSprite.setTexture(camTexture);
	camSprite.setPosition(640.f, 50.f);
	window.draw(camSprite);

	cv::waitKey(10);
	
}

bool ManualControlState::update(sf::Time dt)
{
	arrowUp.setTexture(getContext().textures->get(Textures::Arrow));
	arrowDown.setTexture(getContext().textures->get(Textures::Arrow));
	arrowLeft.setTexture(getContext().textures->get(Textures::Arrow));
	arrowRight.setTexture(getContext().textures->get(Textures::Arrow));

	watButton.setTexture(getContext().textures->get(Textures::ButtonGreen));

	isUp = false;
	isDown = false;
	isLeft = false;
	isRight = false;
	isWatering = false;

	if (isMeasuring != true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			arrowUp.setTexture(getContext().textures->get(Textures::ArrowRed));
			isUp = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			arrowDown.setTexture(getContext().textures->get(Textures::ArrowRed));
			isDown = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			arrowLeft.setTexture(getContext().textures->get(Textures::ArrowRed));
			isLeft = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			arrowRight.setTexture(getContext().textures->get(Textures::ArrowRed));
			isRight = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			watButton.setTexture(getContext().textures->get(Textures::ButtonRed));
			isWatering = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			mesButton.setTexture(getContext().textures->get(Textures::ButtonRed));
			isMeasuring = true;
		}
	}

	Manual pack;

	pack.Command = "stop";
	pack.Water = false;

	if (isUp) {
		if (isLeft) {
			pack.Command = "for-left";
		}
		else if (isRight) {
			pack.Command = "for-right";
		}
		else {
			pack.Command = "foreward";
		}
	}
	else if(isDown) {
		if (isLeft) {
			pack.Command = "back-left";
		}
		else if (isRight) {
			pack.Command = "back-right";
		}
		else {
			pack.Command = "backward";
		}
	}
	else if (isLeft) {
		pack.Command = "left";
	}
	else if (isRight) {
		pack.Command = "right";
	}

	if (isWatering) {
		pack.Water = true;
	}
	else {
		pack.Water = false;
	}

	if (isMeasuring) {
		pack.Command = "measure";
		pack.Water = false;
	}

	std::cout << "Komenda: " << pack.Command.toAnsiString().c_str() << "\nPodlewanie: " << pack.Water << std::endl;
	getContext().connection->sendPacket(pack);

	return true;
}

bool ManualControlState::handleEvent(const sf::Event& event)
{

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Space) {
			requestStackPush(States::Pause);
		}
	}

	return true;
}

