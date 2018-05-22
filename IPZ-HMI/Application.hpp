#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "StateStack.hpp"
#include "UDP.hpp"

class CApplication : private sf::NonCopyable
{
public:
	CApplication();
	~CApplication();
	void run();

private:
	void processEvents();
	void update(sf::Time dt);
	void render();
	void registerStates();

private:
	static const sf::Time TimePerFrame;

	TextureHolder mTextures;
	FontHolder mFonts;
	sf::RenderWindow mWindow;

	StateStack mStateStack;

	CUDP Connection;
};
