#ifndef BOOK_MENUSTATE_HPP
#define BOOK_MENUSTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"


class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);
	~MenuState();

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	void updateOptionText();

private:
	enum OptionNames
	{
		Play,
		Config,
		Authors,
		Exit,
		Test,
	};


private:
	sf::Sprite mBackgroundSprite;
	sf::Sprite mConnection;

	std::vector<sf::Text> mOptions;
	std::size_t mOptionIndex;
	bool wasZeroed;

	TextureHolder mTextures;
};

#endif // BOOK_MENUSTATE_HPP
