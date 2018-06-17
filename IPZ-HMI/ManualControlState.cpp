#include "ManualControlState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include <iostream>
#include "Przetwarzanie_obrazu.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <Windows.h>


#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <ctime>

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

ManualControlState::ManualControlState(StateStack& stack, Context context)
	: State(stack, context)
	, cap("http://" + context.connection->getIP().toString() + ":8080/stream/video.mjpeg")
	, cap2("http://" + context.connection->getIP().toString() + ":8090/stream/video.mjpeg")
	, isUp(false)
	, isDown(false)
	, isLeft(false)
	, isRight(false)
	, startMeasure(false)
	, isWatering(false)
	, Busy(false)
	, duringMeasure(false)
{
	context.window->setKeyRepeatEnabled(false);

	std::time_t tp = std::time(NULL);   // current time, an integer
										// counting seconds since epoch

	std::tm * ts = std::localtime(&tp); // parsed into human conventions

	std::string currentDate = "";
	currentDate += toString(ts->tm_mday);
	currentDate += "-";
	currentDate += toString(ts->tm_mon + 1);
	currentDate += "-";
	currentDate += toString(1900 + ts->tm_year);
	dirDate = currentDate;
	std::string toConvert = "Results/" + dirDate;


	std::wstring stemp = s2ws(toConvert);
	LPCWSTR Directory = stemp.c_str();

	if (CreateDirectory(Directory, NULL))
	{
		std::cout << "Utworzylem katalog" << std::endl;
	}
	else if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		std::cout << "Katalog istnieje" << std::endl;
	}
	else
	{
		
		std::cout << "Jest problem: " << toConvert.c_str() << std::endl;
		system("PAUSE");
	}

	std::string fileDirectory = "Results/" + dirDate + "/results.txt";
	std::cout << "Sciezka: " << fileDirectory << std::endl;


	file.open(fileDirectory, std::ios::app);
	if (file.good() == true)
	{
		std::cout << "Uzyskano dostep do pliku!" << std::endl;
	}
	else {
		std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
	}

	file << "Wyniki pomiarow. Rozpoczynanie sesji:" << std::endl;

	if (!cap.isOpened()) {
		exit(-1);
	}

	if (!cap2.isOpened()) {
		exit(-1);
	}

	sf::Texture& texture = context.textures->get(Textures::ManualControl);
	sf::Texture& arrow = context.textures->get(Textures::Arrow);
	sf::Texture& button = context.textures->get(Textures::ButtonGreen);
	sf::Texture& gear = context.textures->get(Textures::Gear);

	sf::Font& font = context.fonts->get(Fonts::Main);


	mBackgroundSprite.setTexture(texture);

	//--- Arrows
	arrowUp.setTexture(arrow);
	centerOrigin(arrowUp);
	arrowUp.setPosition(960.f, 650.f);
	arrowUp.rotate(-90);

	arrowDown.setTexture(arrow);
	centerOrigin(arrowDown);
	arrowDown.setPosition(960.f, 970.f);
	arrowDown.rotate(90);

	arrowLeft.setTexture(arrow);
	centerOrigin(arrowLeft);
	arrowLeft.setPosition(800.f, 810.f);
	arrowLeft.rotate(180);

	arrowRight.setTexture(arrow);
	centerOrigin(arrowRight);
	arrowRight.setPosition(1120.f, 810.f);

	//---Buttons
	mesButton.setTexture(button);
	centerOrigin(mesButton);
	mesButton.setPosition(1600.f, 810.f);

	watButton.setTexture(button);
	centerOrigin(watButton);
	watButton.setPosition(320.f, 810.f);

	//--- Gear
	Gear.setTexture(gear);
	centerOrigin(Gear);
	Gear.setPosition(1350.f, 910.f);

	//--- A simple menu demonstration

	watInfo.setFont(font);
	watInfo.setString(L"[Q]");
	watInfo.setCharacterSize(60);
	watInfo.setOutlineThickness(2);
	centerOrigin(watInfo);
	watInfo.setPosition(320.f, 940.f);

	watState.setFont(font);
	watState.setString(L"Podlewanie");
	watState.setCharacterSize(60);
	watState.setOutlineThickness(2);
	centerOrigin(watState);
	watState.setPosition(320.f, 670.f);

	mesInfo.setFont(font);
	mesInfo.setString(L"[E]");
	mesInfo.setCharacterSize(60);
	mesInfo.setOutlineThickness(2);
	centerOrigin(mesInfo);
	mesInfo.setPosition(1600.f, 940.f);

	mesState.setFont(font);
	mesState.setString(L"Pomiar");
	mesState.setCharacterSize(60);
	mesState.setOutlineThickness(2);
	centerOrigin(mesState);
	mesState.setPosition(1600.f, 670.f);

	gearVal.setFont(font);
	gearVal.setString(L"1");
	gearVal.setCharacterSize(60);
	gearVal.setOutlineThickness(2);
	centerOrigin(gearVal);
	gearVal.setPosition(1350.f, 820.f);

	gearInfo.setFont(font);
	gearInfo.setString(L"[R/F]");
	gearInfo.setCharacterSize(40);
	gearInfo.setOutlineThickness(2);
	centerOrigin(gearInfo);
	gearInfo.setPosition(1350.f, 1000.f);

	//--- Measures
	currentMesInfo.setFont(font);
	currentMesInfo.setString(L"Ostatni pomiar:");
	currentMesInfo.setCharacterSize(60);
	currentMesInfo.setOutlineThickness(2);
	centerOrigin(currentMesInfo);
	currentMesInfo.setPosition(320.f, 100.f);

	mesHumidityInfo.setFont(font);
	mesHumidityInfo.setString(L"Wilgotnoœæ:");
	mesHumidityInfo.setCharacterSize(40);
	mesHumidityInfo.setOutlineThickness(2);
	mesHumidityInfo.setPosition(100.f, 160.f);

	mesTemperatureInfo.setFont(font);
	mesTemperatureInfo.setString(L"Temperatura gleby:");
	mesTemperatureInfo.setCharacterSize(40);
	mesTemperatureInfo.setOutlineThickness(2);
	mesTemperatureInfo.setPosition(100.f, 210.f);

	mesInsolationInfo.setFont(font);
	mesInsolationInfo.setString(L"Nas³onecznienie:");
	mesInsolationInfo.setCharacterSize(40);
	mesInsolationInfo.setOutlineThickness(2);
	mesInsolationInfo.setPosition(100.f, 260.f);

	mesHumidityVal.setFont(font);
	mesHumidityVal.setString(L"b/d");
	mesHumidityVal.setCharacterSize(40);
	mesHumidityVal.setOutlineThickness(2);
	mesHumidityVal.setPosition(500.f, 160.f);

	mesTemperatureVal.setFont(font);
	mesTemperatureVal.setString(L"b/d");
	mesTemperatureVal.setCharacterSize(40);
	mesTemperatureVal.setOutlineThickness(2);
	mesTemperatureVal.setPosition(500.f, 210.f);

	mesInsolationVal.setFont(font);
	mesInsolationVal.setString(L"b/d");
	mesInsolationVal.setCharacterSize(40);
	mesInsolationVal.setOutlineThickness(2);
	mesInsolationVal.setPosition(500.f, 260.f);


	gearValue = 1;
	Sample = 1;

}

ManualControlState::~ManualControlState()
{
	file.close();
}


void ManualControlState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	window.draw(arrowUp);
	window.draw(arrowDown);
	window.draw(arrowLeft);
	window.draw(arrowRight);

	window.draw(mesButton);
	window.draw(watButton);

	window.draw(Gear);

	centerOrigin(watInfo);
	window.draw(watInfo);
	centerOrigin(watState);
	window.draw(watState);

	centerOrigin(mesInfo);
	window.draw(mesInfo);
	centerOrigin(mesState);
	window.draw(mesState);

	centerOrigin(gearVal);
	window.draw(gearVal);
	centerOrigin(gearInfo);
	window.draw(gearInfo);

	centerOrigin(currentMesInfo);
	window.draw(currentMesInfo);

	window.draw(mesHumidityInfo);
	window.draw(mesInsolationInfo);
	window.draw(mesTemperatureInfo);
	window.draw(mesHumidityVal);
	window.draw(mesTemperatureVal);
	window.draw(mesInsolationVal);


	//--- Przechwytywanie okna OpenCV
	cv::Mat frameRGB, frameRGBA;

	cap >> frameRGB;

	if (frameRGB.empty())
	{
		std::cout << "Walnal obraz" << std::endl;
		system("PAUSE");
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
	camSprite.setPosition(603.f, 25.f);
	window.draw(camSprite);

	cap2 >> frameRGB;

	if (frameRGB.empty())
	{
		std::cout << "Walnal obraz" << std::endl;
		system("PAUSE");
		return;
	}

	cv::cvtColor(frameRGB, frameRGBA, cv::COLOR_BGR2RGBA);

	cam2Image.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());

	if (!cam2Texture.loadFromImage(cam2Image))
	{
		std::cout << "Brak obrazu" << std::endl;
		return;
	}

	cam2Sprite.setTexture(cam2Texture);
	cam2Sprite.setPosition(1255.f, 25.f);
	window.draw(cam2Sprite);

	cv::waitKey(10);
	
}

bool ManualControlState::update(sf::Time dt)
{
	arrowUp.setTexture(getContext().textures->get(Textures::Arrow));
	arrowDown.setTexture(getContext().textures->get(Textures::Arrow));
	arrowLeft.setTexture(getContext().textures->get(Textures::Arrow));
	arrowRight.setTexture(getContext().textures->get(Textures::Arrow));

	watButton.setTexture(getContext().textures->get(Textures::ButtonGreen));

	isUp = false;
	isDown = false;
	isLeft = false;
	isRight = false;
	isWatering = false;

	if (Busy != true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			arrowUp.setTexture(getContext().textures->get(Textures::ArrowRed));
			isUp = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			arrowDown.setTexture(getContext().textures->get(Textures::ArrowRed));
			isDown = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			arrowLeft.setTexture(getContext().textures->get(Textures::ArrowRed));
			isLeft = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			arrowRight.setTexture(getContext().textures->get(Textures::ArrowRed));
			isRight = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			watButton.setTexture(getContext().textures->get(Textures::ButtonRed));
			isWatering = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			mesButton.setTexture(getContext().textures->get(Textures::ButtonRed));
			startMeasure = true;
		}
		
	}

	Manual pack;

	pack.Command = "stop";
	pack.Water = false;
	pack.Gear = gearValue;
	
	if (Busy == true) {
		dataSet data;
		data = getContext().connection->getData();

		if ((data.Humidity != -1) && (data.Temperature != -1) && (data.Insolation != -1)) {
			mesHumidityVal.setString(toString(data.Humidity));
			mesTemperatureVal.setString(toString(data.Temperature));
			mesInsolationVal.setString(toString(data.Insolation));
			file << Sample << " " << data.Humidity << " " << data.Temperature << " " << data.Insolation << std::endl;
			if (!cam2Image.saveToFile("Results/"+dirDate+"/"+toString(Sample) + ".png")) {
				return -1;
			}
			Sample++;
			Busy = false;
			mesButton.setTexture(getContext().textures->get(Textures::ButtonGreen ));
		}
		else {
			std::cout << "Czekam na dane z czujnikow" << std::endl;
		}
	}
	else {
		if (isUp) {
			if (isLeft) {
				pack.Command = "for-left";
			}
			else if (isRight) {
				pack.Command = "for-right";
			}
			else {
				pack.Command = "foreward";
			}
		}
		else if (isDown) {
			if (isLeft) {
				pack.Command = "back-left";
			}
			else if (isRight) {
				pack.Command = "back-right";
			}
			else {
				pack.Command = "backward";
			}
		}
		else if (isLeft) {
			pack.Command = "left";
		}
		else if (isRight) {
			pack.Command = "right";
		}

		if (isWatering) {
			pack.Water = true;
		}
		else {
			pack.Water = false;
		}

		if (startMeasure) {
			startMeasure = false;
			pack.Command = "measure";
			pack.Water = false;
			Busy = true;
		}

		std::cout << "Komenda: " << pack.Command.toAnsiString().c_str() << "\nPodlewanie: " << pack.Water << "\nBieg: " << pack.Gear << std::endl;
		getContext().connection->sendPacket(pack);
	}

	return true;
}

bool ManualControlState::handleEvent(const sf::Event& event)
{

	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Space) {
			requestStackPush(States::Pause);
		} else if (event.key.code == sf::Keyboard::R) {
			if (gearValue < 3) {
				gearValue++;
				gearVal.setString(toString(gearValue));
			}
		}
		else if (event.key.code == sf::Keyboard::F) {
			if (gearValue > 1) {
				gearValue--;
				gearVal.setString(toString(gearValue));
			}
		}
	}


	return true;
}

