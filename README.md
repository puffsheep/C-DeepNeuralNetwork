# C-DeepNeuralNetwork
This is a Neural Network created in C++ without using libraries to remove general abstraction behind a neural network.

You can either use preexisting data sets and use the `Data` object to initialize it, or use basic arrays and 2D arrays to generate data. In order to use a dataset, there is one main function that is needed.

* `Data.initializeData(file_name, outputs)` will return a vector containing a 2D `.data` array and a 2D `.answer` array that can be used directly in the model. I.e. `dataset.initializeData("data/iris.data", 3)` is a dataset with three outputs using the iris.data file.

* `Model(model_size, model_specs, example_input, DEBUG_MODE = false)` is the constructor used to create the model. `model_size` is the number of layer of the model minus the input layer. `model_specs` is an array that contains the number of nodes in each layer. `example_input` is the representation for the first layer in the model. It is an array of floats that stand for each input. `DEBUG_MODE` is an optional value that will display training data during training. I.e. `Model model(2, {3, 2}, {0.0, 0.0, 0.0, 0.0})` is a model that has an input layer with 4 nodes, one hidden layer with 3 nodes, and an output layer of 2 nodes.

* `Model.train_model(input, answers, iterations, sample_step = 1)` is the method used to train the model. `input` and `answers` are 2D arrays of input data that can be initialized using the `Data` object. `iterations` is the number of training iterations using the data that the model should go through. `sample_step` is an optional value that allows you to reduce the number of samples taken from the training data. A sample step of 2 will divide the data by half as it will skip every other data point whereas a sample step of 3 will divide the data by 3 and skip 2 data points. I.e. `model.train_model(dataset.input, datset.answers, 20000)`

* `Model.run_model(input, sample_step = 1)` is how to run the model and validate its training. `input` is the data that you are using. For an explaination of `sample_step`, see `model.train_model` I.e. `model.run_model(datset.input)`
