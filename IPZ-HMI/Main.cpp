#include <SFML/Audio.hpp>
#include "Application.hpp"

int main()
{
	sf::Music music;
	if (music.openFromFile("Resources/Music/Theme.ogg")) {
		music.play();
	}
	music.setVolume(25);
	music.setLoop(true);

	CApplication app;
	app.run();

	return 0;
}