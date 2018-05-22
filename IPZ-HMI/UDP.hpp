#pragma once
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Structs.hpp"

class CUDP
{
public:
	CUDP();
	CUDP(sf::IpAddress recipient, unsigned short port);
	~CUDP();

private:
	sf::UdpSocket socket;

	sf::Packet pPacket;
	sf::IpAddress iRecipient;
	unsigned short iPort;

public:
	int sendPacket(Package pack);
	void setIP(sf::IpAddress ip);
	void setPort(unsigned short port);
	sf::IpAddress getIP();
	unsigned short getPort();
};

