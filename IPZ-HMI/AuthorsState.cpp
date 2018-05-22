#include "AuthorsState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>


AuthorsState::AuthorsState(StateStack& stack, Context context)
	: State(stack, context)
	, mKierownik()
	, mLewa()
	, mPrawa()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));


	

	mKierownik.setFont(context.fonts->get(Fonts::Main));
	mKierownik.setString(L"Prowadz¹cy: dr hab. in¿. Jacek Reiner, prof. nadzw. PWr\n\nLider: Czes³aw Pruchnik\n");
	mKierownik.setCharacterSize(60);
	mKierownik.setOutlineThickness(2);
	centerOrigin(mKierownik);
	mKierownik.setPosition(context.window->getView().getSize().x / 2.f, 280.f);

	mLewa.setFont(context.fonts->get(Fonts::Main));
	mLewa.setString(L"Micha³ Zawiœlak\nJakub Zgrzebnicki\nMicha³ Ostrowski\nKacper Suchoñ");
	mLewa.setCharacterSize(60);
	mLewa.setOutlineThickness(2);
	centerOrigin(mLewa);
	mLewa.setPosition(context.window->getView().getSize().x / 4.f, context.window->getView().getSize().y / 2.f);

	mPrawa.setFont(context.fonts->get(Fonts::Main));
	mPrawa.setString(L"Agnieszka Przyby³owska\n£ukasz Wiêckowski\nDenis ¯ebrowski\nMateusz Witerski");
	mPrawa.setCharacterSize(60);
	mPrawa.setOutlineThickness(2);
	centerOrigin(mPrawa);
	mPrawa.setPosition(3 * context.window->getView().getSize().x / 4.f, context.window->getView().getSize().y / 2.f);
}

void AuthorsState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	window.draw(mKierownik);
	window.draw(mLewa);
	window.draw(mPrawa);
}

bool AuthorsState::update(sf::Time dt)
{

	return true;
}

bool AuthorsState::handleEvent(const sf::Event& event)
{
	// If key is pressed, trigger the next screen
	if ((event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 3) || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}