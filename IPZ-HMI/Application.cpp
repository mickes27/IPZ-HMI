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
#include <iostream>


const sf::Time CApplication::TimePerFrame = sf::seconds(1.f / 60.f);

CApplication::CApplication()
: mWindow(sf::VideoMode(1920, 1080), "MJR 2017", sf::Style::Fullscreen)
, mTextures()
, mFonts()
, Connection()
, mStateStack(State::Context(mWindow, mTextures, mFonts, Connection))
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
		exit(1);
	}


	registerStates();
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
}
