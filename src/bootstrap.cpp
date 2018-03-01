#include "bootstrap.hpp"

double bootstrap(const DataArray::IDataFunctor &fcn, const DataArray &data, std::default_random_engine &generator, int iterations)
{
	// ``Uniform'' distribution to sample from the data. Arguments are closed interval so need to subtract 1
	// in order to safely index the array.
	std::uniform_int_distribution<int> distribution(0,data.getSize()-1);

	// DataArray to hold the re-sampled estimates on the function error.
	DataArray resampledFncValues;
	resampledFncValues.reserve(iterations);

	// Re-sample the number of times specified by the call.
	for(int i = 0; i < iterations; ++i)
	{
		// Create a data array to hold each n samples.
		DataArray tempData;
		tempData.reserve(data.getSize());

		// Pick randomly n measurements.
		for(int j = 0; j < data.getSize(); ++j)
		{
			tempData.push_back(data[distribution(generator)]);
		}

		// Compute the value of the function on this re-sample and store it.
		double tempValue = fcn(tempData);
		resampledFncValues.push_back(tempValue);

	}

	// Compute the error according to the bootstrap formula.
	double mean 	   = resampledFncValues.mean();
	double meanSquared = resampledFncValues.squareMean();
	double error 	   = sqrt(meanSquared - mean * mean);
	return error;
}