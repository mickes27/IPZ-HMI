#ifndef BOOK_MOVEJSTATE_HPP
#define BOOK_MOVEJSTATE_HPP

#include "State.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class MoveJState : public State
{
public:
	MoveJState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Sprite mBackgroundSprite;
	sf::Sprite mGear;

	TextureHolder mTextures;

	std::vector<sf::Text> mOptions;
	std::size_t mOptionIndex;

	sf::Text sState;
	sf::Text sVelocity;

	bool wasZeroed;

};


#endif // BOOK_MOVEJSTATE_HPP