#ifndef SERVER_H
#define SERVER_H
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/Packet.hpp>

#include <string.h>
class Server
{
	public:
		sf::TcpListener server;
		sf::TcpSocket socket;

		Server()
		{
			std::cout << "Binding Port" << std::endl;
			if ( server.listen ( 4321 ) != sf::Socket::Done ) {
				std::cout << "unable to bind to port" << std::endl;
				return;
			}

			Start();
		}
		void Start()
		{

			std::cout << "Waiting connection" << std::endl;
			if ( server.accept ( socket ) != sf::Socket::Done ) {
				std::cout << "unable to bind sockets" << std::endl;

			}
			Cycle();

		}

		void Cycle()
		{

			sf::Packet packet;
			int a = 5;
			int b = 7;
			packet << a << b;
			std::cout << "Sending packet" << std::endl;
			if ( socket.send ( packet ) != sf::Socket::Done ) {
				std::cout << "unable to send data" << std::endl;
				Start();
				return;

			}
			std::cout << "Receiving packet" << std::endl;
			if ( socket.receive ( packet ) != sf::Socket::Done ) {
				std::cout << "error receiving" << std::endl;
				Start();
				return;
			}
			packet >> a >> b;
			std::cout << a << b << std::endl;
			Cycle();
		}

		virtual ~Server() {}
	protected:
	private:
};

#endif // SERVER_H
