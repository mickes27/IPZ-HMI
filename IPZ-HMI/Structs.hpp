#ifndef BOOK_STRUCTS_HPP
#define BOOK_STRUCTS_HPP

#include <SFML/System.hpp>

struct Package {
	sf::String Command;
	sf::Uint16 Pul;
	bool Dir;
	sf::Uint64 Delay;
};

struct Config {
	int MinAngle;
	int MaxAngle;
	int MidLeft;
	int MidRight;
	int LowHue;
	int HighHue;
	int LowSat;
	int HighSat;
	int LowVal;
	int HighVal;
	int HoughVot;
	int Fill;
	int Destr;
};

#endif // BOOK_STATEIDENTIFIERS_HPP