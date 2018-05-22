#include "UDP.hpp"
#include <iostream>


CUDP::CUDP()
{
	iRecipient = "127.0.0.1";
	iPort = 54000;
}

CUDP::CUDP(sf::IpAddress recipient, unsigned short port)
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
