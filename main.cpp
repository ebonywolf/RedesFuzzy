#include <cmath>
#include <limits>
#include <iostream>
//#include "truck_client.h"
#include "fuzzy_rule_set.h"
#include "MyTruckClient.h"
#include <SFML/Network/Socket.hpp>
#include "Server.h"
#include <fstream>
#include <vector>

#include "source/opennn.h"

using namespace std;

const int PLAYER1_PORT = 4321;
const int PLAYER2_PORT = 4322;
const string DEFAULT_HOST = "localhost";
const int DEFAULT_PORT = PLAYER1_PORT;
#define DATA "data.dat"

namespace rules
{
	constexpr double inf = std::numeric_limits<double>::infinity();

	// Concepts for x
	FuzzySet left ( -inf, -inf, -0.4, 0.0 );
	FuzzySet center ( -0.4, 0.0, 0.0, 0.4 );
	FuzzySet right ( 0.0, 0.4, inf, inf );

	// Concepts for y
	FuzzySet far ( -inf, -inf, 0.2, 0.8 );
	FuzzySet near ( 0.2, 0.8, inf, inf );

	// Concepts for angle
	FuzzySet a_straight ( -5, 0, 0, 5 );
	FuzzySet a_left ( -20, -5, -5, 0 );
	FuzzySet a_right ( 0, 5, 5, 20 );
	FuzzySet a_very_left ( -inf, -inf, -20, -5 );
	FuzzySet a_very_right ( 5, 20, inf, inf );

	// Wildard concept
	FuzzySet any ( -inf, -inf, inf, inf );

	FuzzyRuleSet rules ( {
		FuzzyRule ( left, any, a_very_left, a_very_right ),
		FuzzyRule ( left, any, a_very_right, a_straight ),
		FuzzyRule ( right, any, a_very_left, a_very_left ),
		FuzzyRule ( right, any, a_very_right, a_straight ),
		FuzzyRule ( center, any, a_very_left, a_very_right ),
		FuzzyRule ( center, any, a_very_right, a_very_left ),
		FuzzyRule ( left, far, a_left, a_very_right ),
		FuzzyRule ( left, far, a_right, a_straight ),
		FuzzyRule ( left, far, a_straight, a_very_right ),
		FuzzyRule ( right, far, a_left, a_straight ),
		FuzzyRule ( right, far, a_right, a_very_left ),
		FuzzyRule ( right, far, a_straight, a_very_left ),
		FuzzyRule ( center, far, a_left, a_right ),
		FuzzyRule ( center, far, a_right, a_left ),
		FuzzyRule ( center, any, a_straight, a_straight ),
		FuzzyRule ( left, near, a_left, a_right ),
		FuzzyRule ( left, near, a_right, a_right ),
		FuzzyRule ( left, near, a_straight, a_right ),
		FuzzyRule ( right, near, a_left, a_left ),
		FuzzyRule ( right, near, a_right, a_left ),
		FuzzyRule ( right, near, a_straight, a_left ),
		FuzzyRule ( center, near, a_left, a_right ),
		FuzzyRule ( center, near, a_right, a_left ),
	} );
} // namespace rules
vector<vector<double>> filter ( vector<vector<double>> vetor, double margin )
{
	auto dist = [] ( double a, double b ) {
		double c = a - b;
		if ( c < 0 ) { c *= -1; }
		return c;
	};
	vector<vector<double>> filtered;
	for ( auto x : vetor ) {
        bool add=true;
		for ( auto y : vetor ) {
			double total = 0;
			for ( int i = 0; i < x.size(); i++ ) {
			    total+= dist(x[i],y[i]);
			}

		}

	}



}





int main()
{

//	ofstream output;
	//output.open ( DATA, ios::app );


	//if ( output.is_open() ) {
	OpenNN::NeuralNetwork neuralNetwork("neural_network.xml");

		MyTruckClient client;
		try {
			client.conn ( DEFAULT_HOST, PLAYER1_PORT, 2 );
		} catch ( TruckClientException  &e ) {
			cout << e << endl;
			return main();
		}
		try {
			while ( true ) {
				ServerResponsePackage originalData = client.getTruckData();
                ServerResponsePackage data=originalData;
				// Normalize the angle so that 0.0 points toward the parking lot.
				data.angle = std::fmod ( data.angle + 90, 360.0 ) - 180.0;
				data.x -= 0.5;

				double instruction = rules::rules ( data.x, data.y, data.angle );

				std::cout << "x = " << data.x << " - "
				          << "y = " << data.y << " - "
				          << "angle = " << data.angle << " - "
				          << "sent = " << instruction << '\n';

              //  output<<originalData.x<<'\t'<<originalData.y<<'\t'<<originalData.angle<<'\t'<<instruction<<'\n';
				OpenNN::Vector<double> input;
				input.resize(10);
				input[0]=originalData.x;
				input[1]=originalData.y;
				input[2]=originalData.angle;

				OpenNN::Vector<double> output=neuralNetwork.calculate_outputs(input);

				client.sendTruckInstruction ( output[0] ); // 30 degrees
			}
		} catch ( TruckClientException  &e ) {
			cout << e << endl;
		}
	//} else {
	//	std::cout << "unable to open file" << std::endl;
	//}
//	output.close();


	return main();
}
