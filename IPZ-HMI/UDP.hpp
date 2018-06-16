#pragma once
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "Structs.hpp"
#include <thread>

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

	std::thread* ImageProcessingThread;

public:
	int sendPacket(Package pack);
	int sendPacket(Manual pack);
	int sendPacket(menuStruct pack);
	dataSet getData();
	void setIP(sf::IpAddress ip);
	void setPort(unsigned short port);
	sf::IpAddress getIP();
	unsigned short getPort();
	void registerThread(std::thread* thread);
	std::thread* getThread();
};

