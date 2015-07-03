#ifndef NEURALTRAINER_H
#define NEURALTRAINER_H

#include <iostream>
#include <sstream>
#include <time.h>
#include <stdexcept>

// OpenNN includes

#include <opennn.h>

class NeuralTrainer
{
	public:
		static void train();



		virtual ~NeuralTrainer() {}
	protected:
	private:
};

#endif // NEURALTRAINER_H
