#ifndef BOOK_TESTSTATE_HPP
#define BOOK_TESTSTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <opencv2\opencv.hpp>


class TestState : public State
{
public:
	TestState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mText;

	cv::VideoCapture cap;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
};

#endif // BOOK_TESTSTATE_HPP
