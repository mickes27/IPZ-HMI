#include "UDP.hpp"
#include <iostream>


CUDP::CUDP()
	: socket()
{
	socket.setBlocking(false);
	if (socket.bind(54000) != sf::Socket::Done)
	{
		std::cout << "Nie mozna bindowac socketa" << std::endl;
	}

	iRecipient = "127.0.0.1";
	iPort = 54000;
}

CUDP::CUDP(sf::IpAddress recipient, unsigned short port)
	: socket()
{
	iRecipient = recipient;
	iPort = port;
}


CUDP::~CUDP()
{
}

int CUDP::sendPacket(Package pack)
{
	pPacket << pack.Command<< pack.Pul << pack.Dir << pack.Delay;

	if (socket.send(pPacket, iRecipient, iPort) != sf::Socket::Done)
	{
		std::cout << "Couldn't send" << std::endl;
		return -1;
	}
	else {
		std::cout << "Wyslano: " << pack.Command.toAnsiString() << " " << pack.Pul << " " << pack.Dir << " " << pack.Delay << std::endl;
	}
	pPacket.clear();

	return 0;
}

int CUDP::sendPacket(Manual pack)
{
	pPacket << pack.Command << pack.Water << pack.Gear;

	if (socket.send(pPacket, iRecipient, iPort) != sf::Socket::Done)
	{
		std::cout << "Couldn't send" << std::endl;
		return -1;
	}
	else {
		std::cout << "Wyslano: " << pack.Command.toAnsiString() << " " << pack.Water << " " << pack.Gear << std::endl;
	}
	pPacket.clear();

	return 0;
}

int CUDP::sendPacket(menuStruct pack)
{
	pPacket << pack.menuCommand;

	if (socket.send(pPacket, iRecipient, iPort) != sf::Socket::Done)
	{
		std::cout << "Couldn't send" << std::endl;
		return -1;
	}
	else {
		std::cout << "Wyslano: " << pack.menuCommand.toAnsiString() << " do " << iRecipient << " na port " << iPort << std::endl;
	}
	pPacket.clear();


	return 0;
}

dataSet CUDP::getData()
{
	dataSet recivedData;

	recivedData.Humidity = -1;
	recivedData.Temperature = -1;
	recivedData.Insolation = -1;

	sf::Packet packet;
	sf::IpAddress remoteIP;
	unsigned short remotePort;
	auto status = socket.receive(packet, remoteIP, remotePort);
	if (status == sf::Socket::Done)
	{
		std::cout << "Odbieram dane:" << std::endl;
		
		int tempHumidity;
		int tempTemperature;
		int tempInsolation;
		
		packet >> tempHumidity >> tempTemperature >> tempInsolation;

		if (status == sf::Socket::Done)
		{
			recivedData.Humidity = tempHumidity;
			recivedData.Temperature = tempTemperature;
			recivedData.Insolation = tempInsolation;
		}
		else if (status == sf::Socket::NotReady)
		{
			std::cout << "Nie ma danych" << std::endl;
		}
		else if (status == sf::Socket::Disconnected)
		{
			std::cout << "Nie polaczony" << std::endl;
		}
		else if (status == sf::Socket::Error)
		{
			std::cout << "Blad!!!!!" << std::endl;
		}
	}
	
	return recivedData;

}

void CUDP::setIP(sf::IpAddress ip)
{

	iRecipient = ip;
}

void CUDP::setPort(unsigned short port)
{
	iPort = port;
}

sf::IpAddress CUDP::getIP()
{
	return iRecipient;
}

unsigned short CUDP::getPort()
{
	return iPort;
}

void CUDP::registerThread(std::thread * thread)
{
	ImageProcessingThread = thread;
}

std::thread * CUDP::getThread()
{
	return ImageProcessingThread;
}
