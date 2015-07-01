#include "MyTruckClient.h"
#include <SFML/Network/Packet.hpp>
#include <sstream>

#include <string.h>
using namespace sf;

static ServerResponsePackage _parseTruckData ( char *raw_data )
{
	int i, j;
	char buff[50];
	ServerResponsePackage response;

	i = 0;
	for ( j = 0, buff[j] = raw_data[i];
	        raw_data[i] != '\t';
	        i++, j++, buff[j] = raw_data[i] );
	response.x = atof ( buff );
	i++;

	for ( j = 0, buff[j] = raw_data[i];
	        raw_data[i] != '\t';
	        i++, j++, buff[j] = raw_data[i] );
	response.y = atof ( buff );
	i++;

	for ( j = 0, buff[j] = raw_data[i];
	        raw_data[i] != '\0';
	        i++, j++, buff[j] = raw_data[i] );
	response.angle = atof ( buff );

	return response;
}
static TruckClientException getException(sf::Socket::Status status){
    switch ( status ) {
			case Socket::NotReady :{return TruckClientException ( "Not Ready" ); break;}
			case Socket::Disconnected :{return TruckClientException ( "Disconnected" ); break;}
			case Socket::Error:{return TruckClientException ( "Error" ); break;}
			default:
				break;
		}
}


MyTruckClient::MyTruckClient()
{
	//ctor
}

MyTruckClient::~MyTruckClient()
{
	//dtor
}
void MyTruckClient::conn ( std::string host, int port, int timeout )
{



	sf::Socket::Status status = socket.connect ( IpAddress ( host ), port, sf::seconds ( timeout ) );
	if(status!= sf::Socket::Done ){
            throw getException(status);
	}
}
void MyTruckClient::sendTruckInstruction(double instruction){

    std::ostringstream msg;
    msg << instruction << "\r\n";
    const char* s=msg.str().c_str();
    int size = strlen(s);


   sf::Socket::Status status =socket.send(s, size);

    if(status!= sf::Socket::Done ){
            throw getException(status);
	}


}

ServerResponsePackage MyTruckClient::getTruckData(){



  const char *s="r\r\n";
  int a= strlen(s);

  if( sf::Socket::Done!= socket.send(s,a ) ){
            throw TruckClientException("Cant send message request");
	}else{
        std::cout<< "Sent R" <<std::endl;
	}


	char buffer[200];
	size_t bytesReceived=0;
	std::cout<< "Waiting for info" <<std::endl;
	sf::Socket::Status status =socket.receive ( (void*)buffer, sizeof(buffer),bytesReceived )	;

	if(status!= sf::Socket::Done ){
            throw getException(status);
	}
	if(bytesReceived==0){
        throw TruckClientException("no bytes received");
	}
	void* pointer=buffer;
	std::cout<< "Got info" <<std::endl;



   return _parseTruckData((char *)buffer);


}
