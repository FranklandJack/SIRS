#include "jackKnife.hpp"
#include <iostream>

double jackKnife(const DataArray::IDataFunctor &fcn, const DataArray &data)
{	
	// Create data array to hold the values of the function on the reduced sample sets.
	DataArray reducedFcnValues;
	reducedFcnValues.reserve(data.getSize());

	// Remove one data point at a time.
	for(int i = 0; i < data.getSize(); ++i)
	{
		// Create temporary data array to hold the reduced sample set.
		DataArray tempDataArray;
		tempDataArray.reserve(data.getSize()-1);
		for(int j = 0; j < i; ++j)
		{
			tempDataArray.push_back(data[j]);
		}

		// Make sure we skip the removed data point.
		for(int j = i+1; j < data.getSize(); ++j)
		{
			tempDataArray.push_back(data[j]);
		}

		// Calculate the function on the reduced data set.
		reducedFcnValues.push_back(fcn(tempDataArray));
	}


	// Calculate error according to the formula for jack-knife.
	double mean 	  = reducedFcnValues.mean();
	double squareMean = reducedFcnValues.squareMean();
	double error 	  = sqrt((squareMean - mean * mean) * data.getSize());

	return error;


}
