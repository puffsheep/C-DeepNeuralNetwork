#import"MyNN.h"

int main()
{
	// Set Random Number Seed
	setRandomSeed();

	// Batch of vectors of initial inputs
	std::vector<std::vector<float>> inputs {
		{1.0, 2.0, 3.0, 2.5},
		{2.0, 5.0, -1.0, 2.0},
		{-1.5, 2.7, 3.3, -0.8}
	};

	Data d1;
	d1.initializeData(1);

	//printOutputs(d1.data);
	//printOutputs(d1.answers);

	// Construction of layers
	Layer l1(3, d1.data);
	Layer l2(4, l1);
	Layer l3(4, l2);
	Layer l4(2, l3);

	//printOutputs(d1.answers);
	//printOutputs(l4.layer_outputs);

	l4.calculateLoss(d1.answers);
	printVector(l4.loss);
	//printOutputs(l4.unactivated_layer_outputs);
}
