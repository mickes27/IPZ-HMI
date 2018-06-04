#include "MoveJState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include <iostream>
#include <thread>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MoveJState::MoveJState(StateStack& stack, Context context)
	: State(stack, context)
	, cap(0)
	, sState()
{

	if (!cap.isOpened())
	{
		exit(1);
	}

	sf::Texture& texture = context.textures->get(Textures::TitleScreenFrame);
	sf::Font& font = context.fonts->get(Fonts::Main);


	mBackgroundSprite.setTexture(texture);

	// A simple menu demonstration

	sState.setFont(font);
	sState.setString(L"To ¿yje!");
	sState.setCharacterSize(60);
	sState.setOutlineThickness(2);
	centerOrigin(sState);
	sState.setPosition((context.window->getView().getSize() / 2.f) - sf::Vector2f(0.f, 460.f));

}


void MoveJState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	centerOrigin(sState);
	window.draw(sState);

	//--- Przechwytywanie okna OpenCV
	cv::Mat frameRGB, frameRGBA;
	cap >> frameRGB;

	if (frameRGB.empty())
	{
		system("PAUSE");
		return;
	}

	cv::cvtColor(frameRGB, frameRGBA, cv::COLOR_BGR2RGBA);

	camImage.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());

	if (!camTexture.loadFromImage(camImage))
	{
		system("PAUSE");
		return;
	}

	camSprite.setTexture(camTexture);
	camSprite.setPosition(1214.f, 30.f);

	//--- Threshold
	cap >> frameRGB;

	if (frameRGB.empty())
	{
		system("PAUSE");
		return;
	}

	cv::cvtColor(frameRGB, frameRGBA, cv::COLOR_BGR2RGBA);

	threshholdImage.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());

	if (!threshholdTexture.loadFromImage(threshholdImage))
	{
		system("PAUSE");
		return;
	}

	threshholdSprite.setTexture(threshholdTexture);
	threshholdSprite.setPosition(1219.f, 564.f);

	window.draw(camSprite);
	window.draw(threshholdSprite);
}

bool MoveJState::update(sf::Time dt)
{

	return true;
}

bool MoveJState::handleEvent(const sf::Event& event)
{
	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed) {
		return false;
	}
	
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Space) {
			requestStackPush(States::Pause);
		} 
	}

	return true;
}

