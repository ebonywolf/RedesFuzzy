#include "TruckAi.h"

#include <cmath>
#define TURN 30
#define PI  3.14159265358979323

static double toRadians ( double a )
{
	\
	return  a * PI / 180;
}
static double toDegree ( double a )
{
	\
	return  a * 180 / PI;
}
static  double invertAngle ( double angle )
{
	angle += PI;
	while ( angle - 2 * PI > 0 ) {
		angle -= 2 * PI;
	}
	return angle;
}

TruckAi::TruckAi()
{
	//ctor
}

TruckAi::~TruckAi()
{
	//dtor
}
double process ( ServerResponsePackage info )
{
	info.angle += 90;
	info.angle = toRadians ( info.angle );
	info.angle = invertAngle ( info.angle );
	double y_goal = 0.8;
	double x_goal = 0.5;

	double angleToGoal = ( info.x - x_goal ) / ( info.y / y_goal );
	return 0;





}
