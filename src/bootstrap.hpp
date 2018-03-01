#ifndef bootstrap_hpp
#define bootstrap_hpp

#include "DataArray.hpp"
#include <random>
#include <cmath>
/**
 *\file
 *\brief Function calculate bootstrap error of any function of a DataArray.
 *\param fcn a IDataFunctor reference that acts on the data (this is the function).
 *\param data a DataArray reference the function is a function of.
 *\param generator std::default_random_engine reference for randomly re-sampling.
 *\param iterations integer value representing the number of re-samplings.
 *\return floating point value representing the bootstrap error.
 *
 * Bootstrap error is calculated by performing a specified number of random re-samplings and calculating
 * the value of the function for those re-samples. This function is versatile since it will work with any
 * IDataFunctor reference (which the user can inherit from and define since its operator() is virtual)  and
 * the corresponding bootstrap error can be calculated.
 *
 */
double bootstrap(const DataArray::IDataFunctor &fcn, 
				 const DataArray &data, 
				 std::default_random_engine &generator, 
				 int iterations = 100);

#endif /* bootstrap_hpp */