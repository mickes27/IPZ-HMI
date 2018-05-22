#ifndef BOOK_STRUCTS_HPP
#define BOOK_STRUCTS_HPP

#include <SFML/System.hpp>

struct Package {
	sf::String Command;
	sf::Uint16 Pul;
	bool Dir;
	sf::Uint64 Delay;
};

#endif // BOOK_STATEIDENTIFIERS_HPP