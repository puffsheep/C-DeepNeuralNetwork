// Input data object
class Data
{
private:
	// Sets size limits on data points
	float maxInnerCircle = 0.650;
	float maxOuterCircle = 1.000;

	float minInnerCircle = 0.400;
	float minOuterCircle = 0.750;

public:
	// Generates the two viewable attributes of Data instance
	std::vector<std::vector<float>> data;
	std::vector<std::vector<float>> answers;

private:
	// Generates a Y value for the inner circle based on X
	// Argument is the X value, Y is returned
	float generateYInner(float x)
	{
		// Used to determine if Y is negative (0) or positve (1)
		const int positive = rand() % 2;

		// Randomized circle size
		float minCircleSize = fmax(int(minInnerCircle * 1000), int(x * 1000) + 1);
		float maxCircleSize = int(maxInnerCircle * 1000) - minCircleSize;
		float circle_size = (rand() % int(maxCircleSize) + int(minCircleSize)) * 0.001;

		// Gets the Y value in a triangle where one vertex
		// rests on the circle with a radius set above
		float y = tan(acos(x/circle_size)) * x;

		// Uses the variable from before
		if(positive)
		{
			return y;
		}
		else
		{
			return -y;
		}
	}

	// Generates a Y value for the outer circle based on X
	// Argument is the X value, Y is returned
	float generateYOuter(float x)
	{
		// Used to determine if Y is negative (0) or positve (1)
		int positive = rand() % 2;

		// Randomized circle size with X being used to account for
		// the chances of a radius being smaller than the X value generated
		float minCircleSize = fmax(int(minOuterCircle * 1000), int(x * 1000) + 1);
		float maxCircleSize = int(maxOuterCircle * 1000) - minCircleSize;
		float circle_size = (rand() % int(maxCircleSize) + int(minCircleSize)) * 0.001;

		// Gets the Y value in a triangle where one vertex
		// rests on the circle with a radius set above
		float y = tan(acos(x/circle_size)) * x;

		// Uses the variable from before
		if(positive)
		{
			return y;
		}
		else
		{
			return -y;
		}
	}

public:
	// Generates data randomly assigned to either the
	// inner circle or outer circle which is defined above

	// Argument is the number of data points which
	// gets returned as an array of vectors X, Y
	std::vector<std::vector<float>> initializeData(int size)
	{
		// Iterates creation of data points for
		// the number of data points requested
		for(int i = 0; i < size; i++)
		{
			// Declares the X variable for this data point and creates
			// a variable to determine which circle the data point will lie on
			float x;
			int innerData = rand() % 2;
			data.push_back({});
			if(innerData)
			{
				// Sets the answer to this data point
				// as the inner circle (1, 0)

				// Answers is a float for ease of
				// loss calculations
				answers.push_back({1.0, 0.0});

				// Defines X as a value between 0 and 0.65
				// Since the inner circle cannot take an X value greater than 0.65
				// it is just squashed before being used to generate Y value
				x = ((rand() % 2000) - 1000) * 0.001 * 0.65;
				data[i].push_back(x);
				data[i].push_back(generateYInner(abs(x)));
			}

			else
			{
				// Defines X as a value between 0 and 1.0
				answers.push_back({0.0, 1.0});
				x = ((rand() % 1000) - 1000) * 0.001;
				data[i].push_back(x);
				data[i].push_back(generateYOuter(abs(x)));
			}
		}

		// Returns the array of vectors X, Y
		// [[X, Y], [X, Y], etc.]
		return data;
	}
};