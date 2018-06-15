#include "ConnectionState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include <iostream>
#include <Windows.h>

#include <SFML/Graphics/RenderWindow.hpp>


ConnectionState::ConnectionState(StateStack& stack, Context context)
	: State(stack, context)
	, mOptions()
	, mText()
	, sIP()
	, sPort()
	, mOptionIndex(0)
	, userInput()
	, sState()
	, mTimer(sf::Time::Zero)
{
	wasZeroed = true;
	isConnected = false;
	
	sIP.setString("198.162.137.20");
	sPort.setString("54000");

	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"");
	sState.setCharacterSize(60);
	sState.setOutlineThickness(2);
	centerOrigin(sState);
	sState.setPosition((context.window->getView().getSize() / 2.f) + sf::Vector2f(0.f, 360.f));

	mText.setFont(context.fonts->get(Fonts::Main));
	mText.setString(L"Konfiguracja socketów UDP");
	mText.setOutlineThickness(2);
	mText.setCharacterSize(60);
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize().x / 2.f, 60.f);

	// A simple menu demonstration
	sf::Text ipOption;
	ipOption.setFont(context.fonts->get(Fonts::Main));
	ipOption.setString("IP:");
	ipOption.setOutlineThickness(2);
	ipOption.setCharacterSize(60);
	ipOption.setPosition((context.window->getView().getSize() / 5.f) + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(ipOption);

	sf::Text portOption;
	portOption.setFont(context.fonts->get(Fonts::Main));
	portOption.setString("Port:");
	portOption.setOutlineThickness(2);
	portOption.setCharacterSize(60);
	portOption.setPosition((context.window->getView().getSize() / 5.f) + sf::Vector2f(0.f, 240.f));
	mOptions.push_back(portOption);


	sIP.setFont(context.fonts->get(Fonts::Main));
	sIP.setPosition((context.window->getView().getSize() / 5.f) + sf::Vector2f(120.f, 180.f));
	sIP.setCharacterSize(60);
	sIP.setOutlineThickness(2);
	sPort.setFont(context.fonts->get(Fonts::Main));
	sPort.setPosition((context.window->getView().getSize() / 5.f) + sf::Vector2f(120.f, 240.f));
	sPort.setCharacterSize(60);
	sPort.setOutlineThickness(2);

	updateOptionText();


}

void ConnectionState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	window.draw(mText);

	FOREACH(const sf::Text& text, mOptions)
		window.draw(text);

	sIP.setPosition((getContext().window->getView().getSize() / 5.f) + sf::Vector2f(300.f, 180.f));
	sPort.setPosition((getContext().window->getView().getSize() / 5.f) + sf::Vector2f(300.f, 240.f));
	centerOrigin(sState);
	sState.setPosition((getContext().window->getView().getSize() / 2.f) + sf::Vector2f(0, 360.f));
	window.draw(sIP);
	window.draw(sPort);
	window.draw(sState);
}

bool ConnectionState::update(sf::Time dt)
{
	if (isConnected) {
		mTimer += dt;

		if (mTimer >= sf::seconds(1.0f))
		{
			requestStackPop();
			requestStackPush(States::Menu);
		}
	}
	return true;
}

bool ConnectionState::handleEvent(const sf::Event& event)
{

	if (event.type == sf::Event::TextEntered)
	{
		switch (mOptionIndex) {
		case 0:
			userInput = sIP.getString();
			break;
		case 1:
			userInput = sPort.getString();
			break;
		}

		if (event.text.unicode == '\b') {
			if (userInput.getSize() > 0) {
				userInput.erase(userInput.getSize() - 1, 1);
			}
		}
		else if (event.text.unicode == '\n' || event.text.unicode == '\r') {

		}
		else if (event.text.unicode < 128) {
			userInput += event.text.unicode;
		}

		switch (mOptionIndex) {
		case 0:
			sIP.setString(userInput);
			break;
		case 1:
			sPort.setString(userInput);
			break;
		}

	}

	if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyPressed) {
		
		
		if (event.joystickButton.button == 1 || event.key.code == sf::Keyboard::Return)
		{
			//Utworz polaczenie
			getContext().connection->setIP(sIP.getString().toAnsiString());
			getContext().connection->setPort(atoi(sPort.getString().toAnsiString().c_str()));
			
				sState.setFillColor(sf::Color::Green);
				sState.setString(L"Ustawiono dane Socketa");
				isConnected = true;
			
		}
		else if (event.key.code == sf::Keyboard::Up) {
			if (mOptionIndex > 0)
				mOptionIndex--;
			else
				mOptionIndex = mOptions.size() - 1;

			userInput.clear();
			updateOptionText();
		}
		else if (event.key.code == sf::Keyboard::Down) {
			if (mOptionIndex < mOptions.size() - 1)
				mOptionIndex++;
			else
				mOptionIndex = 0;

			userInput.clear();
			updateOptionText();
		} 
	}
	else if (event.type == sf::Event::JoystickMoved) {

		if ((event.joystickMove.axis == sf::Joystick::Y) && (event.joystickMove.position <= -15))
		{

			if (wasZeroed == true) {
				// Decrement and wrap-around
				if (mOptionIndex > 0)
					mOptionIndex--;
				else
					mOptionIndex = mOptions.size() - 1;

				updateOptionText();
				wasZeroed = false;
			}
		}

		else if ((event.joystickMove.axis == sf::Joystick::Y) && (event.joystickMove.position >= 15))
		{
			if (wasZeroed == true) {
				// Increment and wrap-around
				if (mOptionIndex < mOptions.size() - 1)
					mOptionIndex++;
				else
					mOptionIndex = 0;

				updateOptionText();
				wasZeroed = false;
			}
		}
		else if (((event.joystickMove.axis == sf::Joystick::Y) && (event.joystickMove.position <= 15)) || ((event.joystickMove.axis == sf::Joystick::Y) && (event.joystickMove.position >= -15))) {
			wasZeroed = true;
		}
	}

	return true;
}

void ConnectionState::updateOptionText()
{
	if (mOptions.empty())
		return;

	// White all texts
	FOREACH(sf::Text& text, mOptions)
		text.setFillColor(sf::Color::White);

	// Red the selected text
	mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}