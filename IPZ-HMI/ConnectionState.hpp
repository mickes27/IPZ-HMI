#ifndef BOOK_CONNECTIONSTATE_HPP
#define BOOK_CONNECTIONSTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class ConnectionState : public State
{
public:
	ConnectionState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

	void updateOptionText();

private:
	enum OptionNames
	{
		IP,
		Port,
	};

private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mText;

	sf::String userInput;
	sf::Text sIP;
	sf::Text sState;
	sf::Text sPort;

	std::size_t mOptionIndex;
	std::vector<sf::Text> mOptions;

	sf::Time			mTimer;

	bool wasZeroed;
	bool isConnected;
};

#endif // BOOK_CONNECTIONSTATE_HPP
