#ifndef TRUCKAI_H
#define TRUCKAI_H
#include "MyTruckClient.h"

class TruckAi
{
	public:

		TruckAi();
		double process ( ServerResponsePackage info );

		virtual ~TruckAi();
	protected:
	private:
};

#endif // TRUCKAI_H
