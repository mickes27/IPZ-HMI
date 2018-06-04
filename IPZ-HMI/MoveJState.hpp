#ifndef BOOK_MOVEJSTATE_HPP
#define BOOK_MOVEJSTATE_HPP

#include "State.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <opencv2/opencv.hpp>


class MoveJState : public State
{
public:
	MoveJState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Sprite mBackgroundSprite;

	TextureHolder mTextures;

	sf::Text sState;

	cv::VideoCapture cap;
	sf::Image camImage;
	sf::Texture camTexture;
	sf::Sprite camSprite;

	sf::Image threshholdImage;
	sf::Texture threshholdTexture;
	sf::Sprite threshholdSprite;
};


#endif // BOOK_MOVEJSTATE_HPP