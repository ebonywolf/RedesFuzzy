#ifndef MYTRUCKCLIENT_H
#define MYTRUCKCLIENT_H


#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <iostream>
struct ServerResponsePackage{
    double x;
    double y;
    double angle;
    ServerResponsePackage():
        x(0),
        y(0),
        angle(0){}
};
struct TruckClientException{
    std::string a;
    TruckClientException(std::string a):a(a){}
    friend std::ostream& operator<<(std::ostream& os,TruckClientException& e){
        os<< e.a;
        return os;
    }

};

class MyTruckClient
{
    public:

        MyTruckClient();
        void conn(std::string host, int port,int timeout=10);
        ServerResponsePackage getTruckData();
        void sendTruckInstruction(double instruction);


        virtual ~MyTruckClient();
    protected:
        sf::TcpSocket socket;
    private:
};

#endif // MYTRUCKCLIENT_H
