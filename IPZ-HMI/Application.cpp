#include "Application.hpp"
#include "StringHelpers.h"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "TitleState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "AuthorsState.hpp"
#include "ConnectionState.hpp"
#include "MoveJState.hpp"
#include "ConfigState.hpp"
#include "TestState.hpp"
#include "ManualControlState.hpp"
#include <iostream>


const sf::Time CApplication::TimePerFrame = sf::seconds(1.f / 60.f);

CApplication::CApplication()
: mWindow(sf::VideoMode(1920, 1080), "IPZ", sf::Style::Fullscreen)
, mTextures()
, mFonts()
, Connection()
, imageProcessing()
, mStateStack(State::Context(mWindow, mTextures, mFonts, Connection, imageProcessing))
{

	mWindow.setFramerateLimit(60);
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setMouseCursorVisible(false);

	// Try to load fonts
	try
	{
		mFonts.load(Fonts::Main, "Resources/Fonts/Sansation.ttf");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		system("PAUSE");
		exit(1);
	}

	// Try to load textures
	try
	{
		//mTextures.load(Textures::Gear, "Resources/Textures/gear.jpg");
		mTextures.load(Textures::TitleScreen, "Resources/Textures/TitleScreen.jpg");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		system("PAUSE");
		exit(1);
	}

	try
	{
		mTextures.load(Textures::TitleScreenFrame, "Resources/Textures/TitleScreenFrame.png");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		system("PAUSE");
		exit(1);
	}

	try
	{
		mTextures.load(Textures::ManualControl, "Resources/Textures/ManualControl.png");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		system("PAUSE");
		exit(1);
	}

	try
	{
		mTextures.load(Textures::Arrow, "Resources/Textures/arrow.png");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		system("PAUSE");
		exit(1);
	}

	try
	{
		mTextures.load(Textures::ArrowRed, "Resources/Textures/arrow_red.png");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		system("PAUSE");
		exit(1);
	}

	try
	{
		mTextures.load(Textures::ButtonGreen, "Resources/Textures/button_green.png");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		system("PAUSE");
		exit(1);
	}

	try
	{
		mTextures.load(Textures::ButtonRed, "Resources/Textures/button_red.png");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		system("PAUSE");
		exit(1);
	}

	try
	{
		mTextures.load(Textures::Gear, "Resources/Textures/Gear.png");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		system("PAUSE");
		exit(1);
	}


	registerStates();
	//mStateStack.pushState(States::Test);
	mStateStack.pushState(States::Title);
}


CApplication::~CApplication()
{
}

void CApplication::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);

			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
			{
				mWindow.close();
			}
		}

		render();
	}
}

void CApplication::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void CApplication::update(sf::Time dt)
{

	mStateStack.update(dt);

}

void CApplication::render()
{
	mWindow.clear();
	mStateStack.draw();

	mWindow.display();
}

void CApplication::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<ConnectionState>(States::Connection);
	mStateStack.registerState<AuthorsState>(States::Authors);
	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<MoveJState>(States::MoveJ);
	mStateStack.registerState<ManualControlState>(States::ManualControl);
	mStateStack.registerState<ConfigState>(States::Config);
	mStateStack.registerState<TestState>(States::Test);
}
