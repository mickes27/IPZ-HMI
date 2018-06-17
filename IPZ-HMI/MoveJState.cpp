#include "MoveJState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include <iostream>
#include <thread>
#include "Przetwarzanie_obrazu.hpp"
#include <Windows.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <mutex>


MoveJState::MoveJState(StateStack& stack, Context context)
	: State(stack, context)
	, sState()
{
	isScaled = false;
	//auto f1 = std::async(&MoveJState::startImageProccessing, this);
	startThread();
	//ImageProccessingThread = new std::thread(&Przetwarzanie_obrazu::start, context.imageproc, toString(getContext().connection->getIP()), getContext().connection->getPort());

	

	sf::Texture& texture = context.textures->get(Textures::TitleScreenFrame);
	sf::Font& font = context.fonts->get(Fonts::Main);


	mBackgroundSprite.setTexture(texture);

	// A simple menu demonstration

	sState.setFont(font);
	sState.setString(L"To ¿yje!");
	sState.setCharacterSize(60);
	sState.setOutlineThickness(2);
	centerOrigin(sState);
	sState.setPosition((context.window->getView().getSize() / 2.f) - sf::Vector2f(0.f, 460.f));

}

MoveJState::~MoveJState()
{
	ImageProccessingThread->join();
}

void MoveJState::startImageProccessing()
{
	getContext().imageproc->changeTest(true);
	getContext().imageproc->start(toString(getContext().connection->getIP()), getContext().connection->getPort());
	

}


void MoveJState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	centerOrigin(sState);
	window.draw(sState);

	cv::Mat frameRGB, frameRGBA;
	std::mutex mtx;

	//--- Przechwytywanie okna OpenCV
	mtx.lock();
	frameRGB = getContext().imageproc->getResults()->clone();
	mtx.unlock();
	
	if (frameRGB.empty())
	{
		std::cout << "Walnal obraz" << std::endl;
		return;
	}
	
	cv::cvtColor(frameRGB, frameRGBA, cv::COLOR_BGR2RGBA);

	camImage.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());

	if (!camTexture.loadFromImage(camImage))
	{
		std::cout << "Brak obrazu" << std::endl;
		return;
	}

	camSprite.setTexture(camTexture);
	camSprite.setPosition(1250.f, 200.f);

	window.draw(camSprite);
	
	//--- Threshold
	mtx.lock();
	frameRGB = getContext().imageproc->getThreshholded()->clone();
	mtx.unlock();

	if (frameRGB.empty())
	{
		std::cout << "Brak obrazu" << std::endl;
		return;
	}

	cv::cvtColor(frameRGB, frameRGBA, cv::COLOR_GRAY2RGBA);

	threshholdImage.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());

	if (!threshholdTexture.loadFromImage(threshholdImage))
	{
		std::cout << "Brak obrazu" << std::endl;
		return;
	}

	threshholdSprite.setTexture(threshholdTexture);
	threshholdSprite.setPosition(1250.f, 628.f);

	
	window.draw(threshholdSprite);
}

bool MoveJState::update(sf::Time dt)
{

	return true;
}

bool MoveJState::handleEvent(const sf::Event& event)
{
	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed) {
		return false;
	}
	
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Space) {
			//ImageProccessingThread->join();
			requestStackPush(States::Pause);
		} 
	}

	return true;
}

void MoveJState::startThread()
{
	std::cout << "Rozpoczynam nowy watek";
	ImageProccessingThread = new std::thread(&MoveJState::startImageProccessing, this);
	getContext().connection->registerThread(ImageProccessingThread);
}

