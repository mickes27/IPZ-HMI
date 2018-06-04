#include "TestState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/View.hpp>



TestState::TestState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
	, cap(0)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	if (!cap.isOpened())
	{
		exit(1);
	}
	
}

void TestState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	cv::Mat frameRGB, frameRGBA;

	cap >> frameRGB;

	if (frameRGB.empty())
	{
		return;
	}

	cv::cvtColor(frameRGB, frameRGBA, cv::COLOR_BGR2RGBA);

	image.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());

	if (!texture.loadFromImage(image))
	{
		return;
	}

	sprite.setTexture(texture);
	window.draw(sprite);
}

bool TestState::update(sf::Time dt)
{
	

	return true;
}

bool TestState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::JoystickMoved || event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
	}

	return true;
}