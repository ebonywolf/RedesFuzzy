#include "NeuralTrainer.h"

using namespace OpenNN;

void NeuralTrainer::train()
{
	try {
		std::cout << "OpenNN. Simple Pattern Recognition Application." << std::endl;

		srand ( ( unsigned ) time ( NULL ) );

		// Data set object

		DataSet data_set;
		data_set.load_data ( "data/data.dat" );

		VariablesInformation* variables_information_pointer = data_set.get_variables_information_pointer();

		variables_information_pointer->set_name ( 0, "x1" );
		variables_information_pointer->set_name ( 1, "x2" );
		variables_information_pointer->set_name ( 2, "x3" );
		variables_information_pointer->set_name ( 3, "y" );

		InstancesInformation* instances_information_pointer = data_set.get_instances_information_pointer();

		instances_information_pointer->split_random_indices ( 0.75, 0.0, 0.25 );

		Vector< Vector<std::string> > variables_information = variables_information_pointer->arrange_inputs_targets_information();

		const Vector< Vector<double> > variables_statistics = data_set.scale_inputs();

		// Neural network object

		NeuralNetwork neural_network ( 3, 25, 1 );

		neural_network.set_inputs_outputs_information ( variables_information );
		neural_network.set_inputs_outputs_statistics ( variables_statistics );

		neural_network.set_scaling_layer_flag ( false );

		// Performance functional

		PerformanceFunctional performance_functional ( &neural_network, &data_set );

		// Training strategy

		TrainingStrategy training_strategy ( &performance_functional );

		TrainingStrategy::Results training_stategy_results = training_strategy.perform_training();

		neural_network.set_scaling_layer_flag ( true );


//testing analysis

		TestingAnalysis testing_analysis ( &neural_network, &data_set );

		testing_analysis.construct_pattern_recognition_testing();

		PatternRecognitionTesting* pattern_recognition_testing_pointer = testing_analysis.get_pattern_recognition_testing_pointer();

		// Save results


		neural_network.save ( "data/neural_network.xml" );
		neural_network.load ( "data/neural_network.xml" );




	} catch ( std::exception& e ) {
		std::cerr << e.what() << std::endl;

	}




}
